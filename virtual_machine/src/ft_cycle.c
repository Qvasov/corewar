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
	if (g_op[cursor->op].args_type_code)
	{
		cursor->byte_to_next_op = 2;
		if (1 <= g_op[cursor->op].args_count)
			cursor->byte_to_next_op += data->size[args_code.a.arg1];
		if (2 <= g_op[cursor->op].args_count)
			cursor->byte_to_next_op += data->size[args_code.a.arg2];
		if (3 <= g_op[cursor->op].args_count)
			cursor->byte_to_next_op += data->size[args_code.a.arg3];
		if (4 <= g_op[cursor->op].args_count)
			cursor->byte_to_next_op += data->size[args_code.a.arg4];
	}
	else
		cursor->byte_to_next_op = 1 + data->size[DIR_CODE];
}

static void	do_op(t_data *data, t_cur *cursor, void (**op) (t_data *, t_cur *))
{
	int				num_player;

	if (data->web_flag)
	{
		num_player = cursor->reg[0] * -1;
		if (num_player > 0 && num_player <= data->vm.num_of_players)
		{
			--data->web.curs[num_player - 1][cursor->op];
			++data->web.curs[num_player - 1][0];
		}
	}
	op[cursor->op](data, cursor);
	if (data->web_flag)
		cursor->op = 0;
}

static void	action(t_data *data, t_cur *cursor)
{
	(data->web_flag) ? web_cur_before_do(data, cursor) : 0;
	if (cursor->op >= LIVE && cursor->op <= AFF)
	{
		data->size[DIR_CODE] = (g_op[cursor->op].dir_size) ? 2 : DIR_SIZE;
		if (ft_valid_op_code_and_reg(data, cursor))
			skip_op(data, cursor);
		else
			do_op(data, cursor, data->op);
		if (ft_bit_check(data->v_flag, 4) &&
		!(cursor->carry == 1 && cursor->op == ZJMP))
			flag_v16(data, cursor);
		cursor->pc = (cursor->pc + cursor->byte_to_next_op) % MEM_SIZE;
	}
	else
		cursor->pc = (cursor->pc + 1) % MEM_SIZE;
	(data->web_flag) ? web_cur_after_do(data, cursor) : 0;
}

void		ft_cycle(t_data *data)
{
	t_cur	*cursor;
	t_vm	*vm;

	vm = &data->vm;
	cursor = vm->cursor;
	while (cursor)
	{
		if (cursor->cycles_to_do_op == 0)
		{
			cursor->op = vm->arena[cursor->pc];
			if (cursor->op >= LIVE && cursor->op <= AFF)
			{
				cursor->cycles_to_do_op = g_op[cursor->op].cycles;
				(data->web_flag) ? web_cur_parse(data, cursor) : 0;
			}
		}
		if (cursor->cycles_to_do_op > 0)
			--cursor->cycles_to_do_op;
		if (cursor->cycles_to_do_op == 0)
			action(data, cursor);
		cursor = cursor->next;
	}
}
