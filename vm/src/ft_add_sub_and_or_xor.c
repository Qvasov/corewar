/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_sub_and_or_xor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 18:32:49 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/30 18:32:49 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	add(t_types_code args_code, t_vm *vm, t_cur *cursor)
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
	cursor->reg[arg[2].num - 1] = cursor->reg[arg[0].num - 1] + cursor->reg[arg[1].num - 1];
	cursor->carry = (cursor->reg[arg[2].num - 1] == 0) ? 1 : 0;
}

void	sub(t_types_code args_code, t_vm *vm, t_cur *cursor)
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
	cursor->reg[arg[2].num - 1] = cursor->reg[arg[0].num - 1] - cursor->reg[arg[1].num - 1];
	cursor->carry = (cursor->reg[arg[2].num - 1] == 0) ? 1 : 0;
}

void	and(t_types_code args_code, t_vm *vm, t_cur *cursor)
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
		arg[0].num = get_ind_value(arg[0], cursor, vm->arena) % IDX_MOD;
	if (args_code.arg2 == REG_CODE)
		arg[1].num = cursor->reg[arg[1].num - 1];
	else if (args_code.arg2 == IND_CODE)
		arg[1].num = get_ind_value(arg[1], cursor, vm->arena) % IDX_MOD;
	cursor->reg[arg[2].num - 1] = arg[0].num & arg[1].num;
	cursor->carry = (cursor->reg[arg[2].num - 1] == 0) ? 1 : 0;
}

void	or(t_types_code args_code, t_vm *vm, t_cur *cursor)
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
		arg[0].num = get_ind_value(arg[0], cursor, vm->arena) % IDX_MOD;
	if (args_code.arg2 == REG_CODE)
		arg[1].num = cursor->reg[arg[1].num - 1];
	else if (args_code.arg2 == IND_CODE)
		arg[1].num = get_ind_value(arg[1], cursor, vm->arena) % IDX_MOD;
	cursor->reg[arg[2].num - 1] = arg[0].num | arg[1].num;
	cursor->carry = (cursor->reg[arg[2].num - 1] == 0) ? 1 : 0;
}

void	xor(t_types_code args_code, t_vm *vm, t_cur *cursor)
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
		arg[0].num = get_ind_value(arg[0], cursor, vm->arena) % IDX_MOD;
	if (args_code.arg2 == REG_CODE)
		arg[1].num = cursor->reg[arg[1].num - 1];
	else if (args_code.arg2 == IND_CODE)
		arg[1].num = get_ind_value(arg[1], cursor, vm->arena) % IDX_MOD;
	cursor->reg[arg[2].num - 1] = arg[0].num ^ arg[1].num;
	cursor->carry = (cursor->reg[arg[2].num - 1] == 0) ? 1 : 0;
}
