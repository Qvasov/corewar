/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st_sti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 19:25:28 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/30 19:25:28 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"



void	st(t_types_code args_code, t_vm *vm, t_cur *cursor)
{
	t_int	arg[2];
	int32_t	addr;
	int8_t	args_size;

	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg2];
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
		vm->arena[addr % MEM_SIZE] = arg[0].byte[3];
		vm->arena[(addr + 1) % MEM_SIZE] = arg[0].byte[2];
		vm->arena[(addr + 2) % MEM_SIZE] = arg[0].byte[1];
		vm->arena[(addr + 3) % MEM_SIZE] = arg[0].byte[0];
	}
}

void	sti(t_types_code args_code, t_vm *vm, t_cur *cursor)
{
	t_int	arg[3];
	int32_t	addr;
	int8_t	args_size;

	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg2];
	arg[2].num = get_arg(args_code.arg3, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg3];
	cursor->byte_to_next_op = args_size;
	if (args_code.arg2 == REG_CODE)
		arg[1].num = cursor->reg[arg[1].num - 1];
	else if (args_code.arg2 == IND_CODE)
		arg[1].num = get_ind_value(arg[1], cursor, vm->arena);
	if (args_code.arg3 == REG_CODE)
		arg[2].num = cursor->reg[arg[2].num - 1];
	arg[0].num = cursor->reg[arg[0].num - 1];
	addr = cursor->pc + ((arg[1].num + arg[2].num) % IDX_MOD);
	if (addr < 0)
		addr = MEM_SIZE + (addr % MEM_SIZE);
	vm->arena[addr % MEM_SIZE] = arg[0].byte[3];
	vm->arena[(addr + 1) % MEM_SIZE] = arg[0].byte[2];
	vm->arena[(addr + 2) % MEM_SIZE] = arg[0].byte[1];
	vm->arena[(addr + 3) % MEM_SIZE] = arg[0].byte[0];
}