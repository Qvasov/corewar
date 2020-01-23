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

static void	do_op(t_vm *vm, t_cursor *cursor)
{
	uint8_t	types_code;
	int16_t pos;

	if (op_tab[cursor->op_code].args_type_code)
	{
		pos = (cursor->position + 1 == MEM_SIZE) ? 0 : cursor->position + 1;
		types_code =  vm->arena[pos];
		if (types_code == op_tab[cursor->position].args_type_code)
		{}//tut ostanovochka
	}
}

void	cursors(t_vm *vm)
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
			if (cursor->op_code >= 0x01 && cursor->op_code <= 0x10)
				do_op(vm, cursor);
		cursor = cursor->next;
	}
}

void	ft_battle(t_vm *vm)
{
	uint64_t	cycle;

	cycle = 0;
	while (++cycle)
	{
		cursors(vm);
	}
}
