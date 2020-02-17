/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op_st_sti.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 20:07:26 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/15 20:07:28 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	change_arena(t_data *data, int32_t addr, t_int arg, t_cur *cursor) //check
{
	int64_t			curs;
	t_vm			*vm;
	int				i;

	vm = &data->vm;
	i = -1;
	while (++i < 4)
	{
		vm->arena[(addr + i) % MEM_SIZE] = arg.byte[3 - i];
		if (data->web_flag)
		{
			if (data->web.change[(addr + i) % MEM_SIZE] / 1000)
				curs = data->web.change[(addr + i) % MEM_SIZE] / 1000;
			else
				curs = data->web.arena[(addr + i) % MEM_SIZE] / 1000;
			data->web.change[(addr + i) % MEM_SIZE] = (uint8_t)arg.byte[3 - i];
			data->web.change[(addr + i) % MEM_SIZE] += (curs * 1000);
		}
	}
}

void	st(t_data *data, t_cur *cursor)
{
	t_int			arg[2];
	int32_t			addr;
	int8_t			args_size;
	t_types_code	args_code;

	args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg2];
	cursor->byte_to_next_op = args_size;

	if (ft_bit_check(data->v_flag, 2) && data->web_flag == 0)
		ft_print_command(arg, args_code, &data->vm, cursor);

	if (args_code.arg2 == REG_CODE)
		cursor->reg[arg[1].num - 1] = cursor->reg[arg[0].num - 1];
	else if (args_code.arg2 == IND_CODE)
	{
		arg[0].num = cursor->reg[arg[0].num - 1]; //конвертация номера регистра в значение, которое находтся в регистре
		arg[1].num = arg[1].num % IDX_MOD;
		addr = cursor->pc + arg[1].num;
		if (addr < 0)
			addr = MEM_SIZE + (addr % MEM_SIZE);
		change_arena(data, addr, arg[0], cursor);
	}
}

void	sti(t_data *data, t_cur *cursor)
{
	t_int			arg[3];
	int32_t			addr;
	int8_t			args_size;
	t_types_code	args_code;

	args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg2];
	arg[2].num = get_arg(args_code.arg3, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg3];
	cursor->byte_to_next_op = args_size;

	if (ft_bit_check(data->v_flag, 2) && data->web_flag == 0)
		ft_print_command(arg, args_code, &data->vm, cursor);

	if (args_code.arg2 == REG_CODE)
		arg[1].num = cursor->reg[arg[1].num - 1];
	else if (args_code.arg2 == IND_CODE)
		arg[1].num = get_ind_value(arg[1], cursor, data->vm.arena);
	if (args_code.arg3 == REG_CODE)
		arg[2].num = cursor->reg[arg[2].num - 1];
	arg[0].num = cursor->reg[arg[0].num - 1];
	addr = cursor->pc + ((arg[1].num + arg[2].num) % IDX_MOD);
	if (addr < 0)
		addr = MEM_SIZE + (addr % MEM_SIZE);
	change_arena(data, addr, arg[0], cursor);
}
