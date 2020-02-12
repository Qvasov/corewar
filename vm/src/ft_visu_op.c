/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_visu_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 17:26:30 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/12 17:26:32 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	change_arena(t_data *data, int32_t addr, t_int arg)
{
	int64_t	buf;
	int		i;

	i = -1;
	while (++i < 4)
	{
		buf = (data->visu.change[addr % MEM_SIZE] / 1000) * 1000;
		data->visu.change[(addr + i) % MEM_SIZE] = arg.byte[3 - i] - data->visu.arena[(addr + i) % MEM_SIZE];
		data->visu.change[(addr + i) % MEM_SIZE] = data->visu.change[(addr + i) % MEM_SIZE];
		data->visu.change[addr % MEM_SIZE] += buf;
	}
}

void 		ft_visu_st(t_types_code args_code, t_data *data, t_cur *cursor)
{
	t_int	arg[op_tab[cursor->op_code].args_count];
	int32_t	addr;
	int8_t	args_size;


	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg2];
	cursor->byte_to_next_op = args_size;
	if (args_code.arg2 == REG_CODE)
		cursor->reg[arg[1].num - 1] = cursor->reg[arg[0].num - 1];
	else if (args_code.arg2 == IND_CODE)
	{
		arg[0].num = cursor->reg[arg[0].num - 1]; //конвертация номера регистра в значение, которое находтся в регистре
		arg[1].num = arg[1].num % IDX_MOD;
		addr = cursor->pc + arg[1].num;
		if (addr < 0)
			addr = MEM_SIZE + (addr % MEM_SIZE);
		change_arena(data, addr, arg[0]);
	}
}

void 		ft_visu_sti(t_types_code args_code, t_data *data, t_cur *cursor)
{
	t_int	arg[3];
	int32_t	addr;
	int8_t	args_size;

	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg2];
	arg[2].num = get_arg(args_code.arg3, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg3];
	cursor->byte_to_next_op = args_size;
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
	change_arena(data, addr, arg[0]);
}
