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

int8_t	size_op(uint8_t op_code, t_types_code args_code, int8_t *size)
{
	int8_t	args_size;

	size[DIR_CODE] = (op_tab[op_code].dir_size) ? 2 : DIR_SIZE;
	args_size = 2;
	if (1 <= op_tab[op_code].args_count)
		args_size += size[args_code.arg1];
	if (2 <= op_tab[op_code].args_count)
		args_size += size[args_code.arg2];
	if (3 <= op_tab[op_code].args_count)
		args_size += size[args_code.arg3];
	if (4 <= op_tab[op_code].args_count)
		args_size += size[args_code.arg4];
	return (args_size);
}

void	skip_op(t_vm *vm, t_cur *cursor)
{
	t_types_code	args_code;

	args_code.num = vm->arena[(cursor->pc + 1) % MEM_SIZE];
	if (op_tab[cursor->op_code].args_type_code)
		cursor->byte_to_next_op = size_op(cursor->op_code, args_code, vm->size);
	else
		cursor->byte_to_next_op = 2;
	cursor->pc = (cursor->pc + cursor->byte_to_next_op) % MEM_SIZE;
}

void	do_op(t_vm *vm, t_cur *cursor, void (**op) (t_types_code, t_vm *, t_cur *))
{
	t_types_code	args_code;

	args_code.num = vm->arena[(cursor->pc + 1) % MEM_SIZE];
	if (cursor->op_code != 0) //для защиты против 0
		op[cursor->op_code](args_code, vm, cursor);
	cursor->pc = (cursor->pc + cursor->byte_to_next_op) % MEM_SIZE;

}

void	cycle(t_vm *vm, int8_t (**type) (int8_t), void (**op) (t_types_code, t_vm *, t_cur *))
{
	t_cur	*cursor;

	cursor = vm->cursor;
	while (cursor)
	{
		if (cursor->cycles_to_do_op == 0) // не то условие флаг передвижения должен быть
		{
			cursor->op_code = vm->arena[cursor->pc];
			if (cursor->op_code >= 0x01 && cursor->op_code <= 0x10)
				cursor->cycles_to_do_op = op_tab[cursor->op_code].cycles;
		}
		if (cursor->cycles_to_do_op > 0)
			--cursor->cycles_to_do_op;
		if (cursor->cycles_to_do_op == 0) //строго if не else if коммменты в кукбуке
		{
			if (cursor->op_code >= 0x01 && cursor->op_code <= 0x10)
			{
				if (ft_valid_op_code_and_reg(vm, cursor, type))
					skip_op(vm, cursor);
				else
					do_op(vm, cursor, op);
			}
			else
				cursor->pc = (cursor->pc + 1) % MEM_SIZE;
		}
		cursor = cursor->next;
	}
}

void	del_cursor(t_vm *vm, t_cur *cursor)
{
	if (cursor->prev)
		cursor->prev->next = cursor->next;
	else
		vm->cursor = cursor->next;
	if (cursor->next)
		cursor->next->prev = (cursor->prev) ? cursor->prev : NULL;
	free(cursor);
}

void	check(t_vm *vm)
{
	t_cur	*cursor;

	cursor = vm->cursor;
	while (cursor)
	{
		if (vm->cycle - cursor->cycle_of_last_live >= vm->cycles_to_die || vm->cycles_to_die <= 0)
			del_cursor(vm, cursor);
		cursor = cursor->next;
	}
	//tut ostanovochka
}

void	ft_battle(t_vm *vm)
{
	int8_t		(*type[4])(int8_t);
	void		(*op[17])(t_types_code, t_vm *, t_cur *);

	ft_set_valid_func(type);
	ft_init_op(op);
	while (++vm->cycle)
	{
		cycle(vm, type, op);
		if (vm->cycle == vm->cycles_to_die || vm->cycles_to_die <= 0)
			check(vm);
	}
}
