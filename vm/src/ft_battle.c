/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_battle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:03:05 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/23 16:03:06 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	do_op(t_vm *vm, t_cursor *cursor, int8_t (**valid) (int8_t))
{
	t_types_code	args_code;
	int16_t 		types_pos;
	int8_t			i;

	if (op_tab[cursor->op_code].args_type_code)
	{
		types_pos = (cursor->position + 1 == MEM_SIZE) ? 0 : cursor->position + 1;
		args_code.num = vm->arena[types_pos];
//		valid[args_code.arg4 - 1](op_tab[cursor->op_code].args.code.type1);
//		valid[args_code.arg3 - 1](op_tab[cursor->op_code].args.code.type2);
		char arg_bits;
		arg_bits = op_tab[cursor->op_code].args.code.type1;
		arg_bits = arg_bits >> (args_code.arg4 - 1);
		if (arg_bits)
			;
		arg_bits = op_tab[cursor->op_code].args.code.type2;
		arg_bits = arg_bits >> (args_code.arg3 - 1);
		if (arg_bits)
			;

//		if (args_code.arg4 == op_tab[cursor->op_code].args.code.type1)
//		{}
//		if (args_code.type3 == op_tab[cursor->op_code].args.code.type2)
//		{}
	}
}

void	cursors(t_vm *vm, int8_t (**type) (int8_t))
{
	t_cursor	*cursor;

	cursor = vm->cursor;
	while (cursor)
	{
		if (cursor->cycles_to_do_op == 0) // не то условие флаг передвижения должен быть
		{
			cursor->op_code = vm->arena[cursor->position];
			cursor->cycles_to_do_op = (cursor->op_code >= 0x01 &&
				cursor->op_code <= 0x10) ? op_tab[cursor->op_code].cycles : 0;
		}
		if (cursor->cycles_to_do_op > 0)
			--cursor->cycles_to_do_op;
		if (cursor->cycles_to_do_op == 0) //строго if не else if коммменты в кукбуке
			if (cursor->op_code >= 0x01 && cursor->op_code <= 0x10) // можно убрать условие
				do_op(vm, cursor, type);
		cursor = cursor->next;
	}
}

static int8_t	valid_arg1(int8_t arg_types /*в таблице*/)
{
	t_bits	arg_bits;
//	int		i;
//	int 	num;
//
//	num = T_REG;
//	i = 0;
//	while (num != 1)
//	{
//		num = num >> 1;
//		++i;
//	}
	arg_bits.num = arg_types;
	if (arg_bits.bit1)
		return (0);
	return (1);
}

static int8_t	valid_arg2(int8_t arg_types)
{
	t_bits	arg_bits;

	arg_bits.num = arg_types;
	if (arg_bits.bit2)
		return (0);
	return (1);
}

static int8_t	valid_arg3(int8_t arg_types)
{
	t_bits	arg_bits;

	arg_bits.num = arg_types;
	if (arg_bits.bit3)
		return (0);
	return (1);
}

static int8_t	valid_arg4(int8_t arg_types)
{
	t_bits	arg_bits;

	arg_bits.num = arg_types;
	if (!arg_bits.bit4)
		return (0);
	return (1);
}

static void	set_valid_func(int8_t (**type) (int8_t))
{
	type[0] = valid_arg1;
	type[1] = valid_arg2;
	type[2] = valid_arg3;
	type[3] = valid_arg4;
}

void	ft_battle(t_vm *vm)
{
	int8_t		(*type[4])(int8_t);
	uint64_t	cycle;

	set_valid_func(type);
	cycle = 0;
	while (++cycle)
	{
		cursors(vm, type);
	}
}
