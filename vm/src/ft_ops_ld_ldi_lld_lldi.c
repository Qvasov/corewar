/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld_ldi_lld_lldi.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 19:25:06 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/30 19:25:07 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ld(t_types_code args_code, t_vm *vm, t_cur *cursor)
{
	t_int	arg[2];
	int8_t	args_size;

	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg2];
	cursor->byte_to_next_op = args_size;
	if (args_code.arg1 == IND_CODE)
		arg[0].num = get_value(arg[0], cursor, vm->arena) % IDX_MOD; // получение числа по адресу
	cursor->reg[arg[1].num - 1] = arg[0].num;
	cursor->carry = (cursor->reg[arg[1].num - 1] == 0) ? 1 : 0;
}

void	ldi(t_types_code args_code, t_vm *vm, t_cur *cursor)
{
	t_int	arg[3];
	int8_t	args_size;

	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg2];
	arg[2].num = get_arg(args_code.arg3, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg3];
	cursor->byte_to_next_op = args_size;
	if (args_code.arg1 == REG_CODE)
		arg[0].num = cursor->reg[arg[0].num - 1];
	else if (args_code.arg1 == IND_CODE)
		arg[0].num = get_value(arg[0], cursor, vm->arena);
	if (args_code.arg2 == REG_CODE)
		arg[1].num = cursor->reg[arg[1].num - 1];
	else if (args_code.arg2 == IND_CODE)
		arg[1].num = get_value(arg[1], cursor, vm->arena);
	cursor->reg[arg[2].num] = (arg[0].num + arg[1].num) % IDX_MOD;
}

void	lld(t_types_code args_code, t_vm *vm, t_cur *cursor)
{
	t_int	arg[2];
	int8_t	args_size;

	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg2];
	cursor->byte_to_next_op = args_size;
	if (args_code.arg1 == IND_CODE) //получение числа по адресу
		arg[0].num = get_value(arg[0], cursor, vm->arena);
	cursor->reg[arg[1].num - 1] = arg[0].num;
	cursor->carry = (cursor->reg[arg[1].num - 1] == 0) ? 1 : 0;
}

void	lldi(t_types_code args_code, t_vm *vm, t_cur *cursor)
{
	t_int	arg[3];
	int8_t	args_size;

	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg2];
	arg[2].num = get_arg(args_code.arg3, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg3];
	cursor->byte_to_next_op = args_size;
	if (args_code.arg1 == REG_CODE)
		arg[0].num = cursor->reg[arg[0].num - 1];
	else if (args_code.arg1 == IND_CODE)
		arg[0].num = get_value(arg[0], cursor, vm->arena);
	if (args_code.arg2 == REG_CODE)
		arg[1].num = cursor->reg[arg[1].num - 1];
	else if (args_code.arg2 == IND_CODE)
		arg[1].num = get_value(arg[1], cursor, vm->arena);
	cursor->reg[arg[2].num] = arg[0].num + arg[1].num;
	cursor->carry = (cursor->reg[arg[2].num - 1] == 0) ? 1 : 0;
}
