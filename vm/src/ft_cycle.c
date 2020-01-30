/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cycle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 18:25:48 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/30 18:25:50 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	skip_op(t_vm *vm, t_cur *cursor)
{
	t_types_code	args_code;

	args_code.num = vm->arena[(cursor->pc + 1) % MEM_SIZE];
	if (op_tab[cursor->op_code].args_type_code)
	{
		cursor->byte_to_next_op = 2;
		if (1 <= op_tab[cursor->op_code].args_count)
			cursor->byte_to_next_op += vm->size[args_code.arg1];
		if (2 <= op_tab[cursor->op_code].args_count)
			cursor->byte_to_next_op += vm->size[args_code.arg2];
		if (3 <= op_tab[cursor->op_code].args_count)
			cursor->byte_to_next_op += vm->size[args_code.arg3];
		if (4 <= op_tab[cursor->op_code].args_count)
			cursor->byte_to_next_op += vm->size[args_code.arg4];
	}
	else
		cursor->byte_to_next_op = 1 + vm->size[DIR_CODE];
	cursor->pc = (cursor->pc + cursor->byte_to_next_op) % MEM_SIZE;
}

static void	do_op(t_vm *vm, t_cur *cursor, void (**op) (t_types_code, t_vm *, t_cur *))
{
	t_types_code	args_code;

	args_code.num = vm->arena[(cursor->pc + 1) % MEM_SIZE];
	op[cursor->op_code](args_code, vm, cursor);

//	printf("P   %d | %s %s\n", cursor->reg[0] * -1, op_tab[cursor->op_code].name, vm->buf.str);

	cursor->pc = (cursor->pc + cursor->byte_to_next_op) % MEM_SIZE;

}

void		ft_cycle(t_vm *vm, int8_t (**type) (int8_t), void (**op) (t_types_code, t_vm *, t_cur *))
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
				vm->size[DIR_CODE] = (op_tab[cursor->op_code].dir_size) ? 2 : DIR_SIZE; //устанавливаем размер T_DIR
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
