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

static void	change_arena(t_data *data, int32_t addr, t_int arg) //check
{
	int64_t	curs;
	int		i;

	i = -1;
	while (++i < 4)
	{
		curs = data->visu.arena[(addr + i) % MEM_SIZE] / 1000;
		curs = curs + (data->visu.change[(addr + i) % MEM_SIZE] / 1000);
		data->visu.change[(addr + i) % MEM_SIZE] = (uint8_t)arg.byte[3 - i];
		data->visu.change[(addr + i) % MEM_SIZE] += (curs * 1000);
	}
}

void 		visuweb_st(t_types_code args_code, t_data *data, t_cur *cursor)
{
	t_int	arg[op_tab[cursor->op_code].args_count];
	int32_t	addr;
	int8_t	args_size;


	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, data->vm.arena, cursor);
//	args_size += data->vm.size[args_code.arg2];
//	cursor->byte_to_next_op = args_size;
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

void 		visuweb_sti(t_types_code args_code, t_data *data, t_cur *cursor)
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
//	args_size += data->vm.size[args_code.arg3];
//	cursor->byte_to_next_op = args_size;
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

void		visuweb_fork(t_types_code args_code, t_data *data, t_cur *cursor)
{
	t_int	arg;
	int8_t	args_size;
	int32_t	addr;
	int		num_player;

	args_size = 1;
	arg.num = get_arg(DIR_CODE, args_size, data->vm.arena, cursor);
//	args_size += data->vm.size[args_code.num];
//	cursor->byte_to_next_op = args_size;

	if (cursor->op_code == 12)
		addr = (cursor->pc + (arg.num % IDX_MOD)) % MEM_SIZE;
	else if (cursor->op_code == 15)
		addr = (cursor->pc + arg.num) % MEM_SIZE;
	if (addr < 0)
		addr += MEM_SIZE;

	num_player = cursor->reg[0] * -1;
	if (num_player > 0 && num_player <= data->vm.num_of_players)
		++data->visu.curs[num_player - 1][0];
	data->visu.change[addr] = data->visu.arena[addr] + 1000;
}

void	lfork_cw(t_types_code args_code, t_vm *vm, t_cur *cursor)
{
	t_int	arg;
	int8_t	args_size;
	int32_t	addr;
	int		num_player;

	args_size = 1;
	arg.num = get_arg(DIR_CODE, args_size, vm->arena, cursor);
//	args_size += vm->size[args_code.num];
//	cursor->byte_to_next_op = args_size;
	new_cursor = ft_copy_cursor(vm, cursor);
	new_cursor->pc = (cursor->pc + arg.num) % MEM_SIZE;
	if (new_cursor->pc < 0)
		new_cursor->pc += MEM_SIZE;

	addr = (cursor->pc + (arg.num % IDX_MOD)) % MEM_SIZE;
}
