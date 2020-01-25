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

void	st(t_cursor *cursor, )
{

}

static int8_t	size_op(uint8_t op_code, t_types_code args_code, int8_t *size)
{
	int8_t	args_size;

	size[DIR_CODE] = (op_tab[op_code].t_dir_size) ? 2 : DIR_SIZE;
	args_size = 2;
	if (1 <= op_tab[op_code].args_count)
		args_size += size[args_code.arg4];
	if (2 <= op_tab[op_code].args_count)
		args_size += size[args_code.arg3];
	if (3 <= op_tab[op_code].args_count)
		args_size += size[args_code.arg2];
	if (4 <= op_tab[op_code].args_count)
		args_size += size[args_code.arg1];
	return (args_size);
}

void	next_op(t_vm *vm, t_cursor *cursor)
{
	t_types_code	args_code;

	args_code.num = vm->arena[(cursor->position + 1) % MEM_SIZE];
	if (op_tab[cursor->op_code].args_type_code)
		cursor->byte_to_next_op = size_op(cursor->op_code, args_code, vm->size);
	else
		cursor->byte_to_next_op = 2;
	cursor->position = (cursor->position + cursor->byte_to_next_op) % MEM_SIZE;
}

void	do_op(t_vm *vm, t_cursor *cursor)
{
	t_types_code	args_code;

	st(cursor, args_code);
	args_code.num = vm->arena[(cursor->position + 1) % MEM_SIZE];
	if (op_tab[cursor->op_code].args_type_code)
		cursor->byte_to_next_op = size_op(cursor->op_code, args_code, vm->size);
	else
		cursor->byte_to_next_op = 2;
	cursor->position = (cursor->position + cursor->byte_to_next_op) % MEM_SIZE;
}

void	cycle(t_vm *vm, int8_t (**type) (int8_t))
{
	t_cursor	*cursor;

	cursor = vm->cursor;
	while (cursor)
	{
		if (cursor->cycles_to_do_op == 0) // не то условие флаг передвижения должен быть
		{
			cursor->op_code = vm->arena[cursor->position];
			if (cursor->op_code >= 0x01 && cursor->op_code <= 0x10)
				cursor->cycles_to_do_op = op_tab[cursor->op_code].cycles;
		}
		if (cursor->cycles_to_do_op > 0)
			--cursor->cycles_to_do_op;
		if (cursor->cycles_to_do_op == 0) //строго if не else if коммменты в кукбуке
		{
			if (cursor->op_code >= 0x01 && cursor->op_code <= 0x10)
			{
				if (ft_check_op(vm, cursor, type))
					next_op(vm, cursor);
				else
					do_op(vm, cursor);
			}
			else
				cursor->position = (cursor->position + 1) % MEM_SIZE;
		}
		cursor = cursor->next;
	}
}

void	ft_battle(t_vm *vm)
{
	int8_t		(*type[4])(int8_t);
	uint64_t	cycles;

	ft_set_valid_func(type);
	cycles = 0;
	while (++cycles)
	{
		cycle(vm, type);
	}
}
