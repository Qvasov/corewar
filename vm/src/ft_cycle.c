/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cycle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 18:25:48 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/30 18:25:50 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	skip_op(t_data *data, t_cur *cursor)
{
	t_types_code	args_code;

	args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
	if (op_tab[cursor->op_code].args_type_code)
	{
		cursor->byte_to_next_op = 2;
		if (1 <= op_tab[cursor->op_code].args_count)
			cursor->byte_to_next_op += data->vm.size[args_code.arg1];
		if (2 <= op_tab[cursor->op_code].args_count)
			cursor->byte_to_next_op += data->vm.size[args_code.arg2];
		if (3 <= op_tab[cursor->op_code].args_count)
			cursor->byte_to_next_op += data->vm.size[args_code.arg3];
		if (4 <= op_tab[cursor->op_code].args_count)
			cursor->byte_to_next_op += data->vm.size[args_code.arg4];
	}
	else
		cursor->byte_to_next_op = 1 + data->vm.size[DIR_CODE];

	int i;
	if (ft_bit_check(data->v_flag, 4) && !(cursor->carry == 1 && cursor->op_code == 0x09))
	{
		ft_printf("ADV %d (0x%.4x -> 0x%.4x) ",
				  cursor->byte_to_next_op,
				  cursor->pc,
				  (cursor->pc + cursor->byte_to_next_op) % MEM_SIZE);
		i = -1;
		while (++i < cursor->byte_to_next_op)
			ft_printf("%.2hhx ", data->vm.arena[cursor->pc + i]);
		ft_printf("\n");
	}

	cursor->pc = (cursor->pc + cursor->byte_to_next_op) % MEM_SIZE;
}

static void	do_op(t_data *data, t_cur *cursor, void (**op) (t_data *, t_cur *))
{
	int				num_player;

	/*if (data->v_flag.bit2 && data->web_flag == 0)
		ft_print_command(&data->vm, cursor);
	else*/ if (data->web_flag)
	{
		num_player = cursor->reg[0] * -1;
		if (num_player > 0 && num_player <= data->vm.num_of_players)
		{
			--data->web.curs[num_player - 1][cursor->op_code];
			++data->web.curs[num_player - 1][0];
		}
	}

	op[cursor->op_code](data, cursor);

	int i;
	if (ft_bit_check(data->v_flag, 4) && !(cursor->carry == 1 && cursor->op_code == 0x09))
	{
		ft_printf("ADV %d (0x%.4x -> 0x%.4x) ",
				  cursor->byte_to_next_op,
				  cursor->pc,
				  (cursor->pc + cursor->byte_to_next_op) % MEM_SIZE);
		i = -1;
		while (++i < cursor->byte_to_next_op)
			ft_printf("%.2hhx ", data->vm.arena[cursor->pc + i]);
		ft_printf("\n");
	}

	cursor->pc = (cursor->pc + cursor->byte_to_next_op) % MEM_SIZE;

	if (data->web_flag)
		cursor->op_code = 0;
}

void		ft_cycle(t_data *data, uint8_t (**valid) (uint8_t, uint8_t), void (**op) (t_data *, t_cur *))
{
	t_cur	*cursor;
	t_vm	*vm;

	vm = &data->vm;
	cursor = vm->cursor;
	while (cursor)
	{
		if (cursor->cycles_to_do_op == 0)
		{
			cursor->op_code = vm->arena[cursor->pc];
			if (cursor->op_code >= 0x01 && cursor->op_code <= 0x10)
			{
				cursor->cycles_to_do_op = op_tab[cursor->op_code].cycles;
				(data->web_flag) ? web_cur_parse(data, cursor) : 0;
			}
		}
		if (cursor->cycles_to_do_op > 0)
			--cursor->cycles_to_do_op;
		if (cursor->cycles_to_do_op == 0)
		{
			(data->web_flag) ? web_cur_before_do(data, cursor) : 0;
			if (cursor->op_code >= 0x01 && cursor->op_code <= 0x10)
			{
				vm->size[DIR_CODE] = (op_tab[cursor->op_code].dir_size) ? 2 : DIR_SIZE; //устанавливаем размер T_DIR
				if (ft_valid_op_code_and_reg(vm, cursor, valid))
					skip_op(data, cursor);
				else
					do_op(data, cursor, op);
			}
			else
				cursor->pc = (cursor->pc + 1) % MEM_SIZE;
			(data->web_flag) ? web_cur_after_do(data, cursor) : 0;
		}
		cursor = cursor->next;
	}
}
