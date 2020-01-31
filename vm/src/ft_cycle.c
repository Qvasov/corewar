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

static void	print_values()
{}

static void	print_command(t_types_code args_code, t_vm *vm, t_cur *cursor)
{
	t_int	arg[3];
	int8_t	args_size;

	ft_printf("P    %d | %s ", cursor->reg[0] * -1, op_tab[cursor->op_code].name);
	args_size = 1;
	(op_tab[cursor->op_code].args_type_code) ? ++args_size : 0;
	arg[0].num = get_arg(args_code.arg1, args_size, vm->arena, cursor);
	if (args_code.arg1 == REG_CODE)
		ft_printf("r%d ", arg[0].num);
	else if (args_code.arg1 == DIR_CODE)
	{
		if (cursor->op_code == 0x02) // усичение
		{}
		ft_printf("%d ", arg[0].num);
	}
	else if (args_code.arg1 == IND_CODE)
	{
		arg[0].num %= IDX_MOD;
		arg[0].num = get_ind_value(arg[0], cursor, vm->arena);
		//условие усечения
		ft_printf("%d ", arg[0].num);
	}

	if (op_tab[cursor->op_code].args_count >= 2)
	{
		args_size += vm->size[args_code.arg1];
		arg[1].num = get_arg(args_code.arg2, args_size, vm->arena, cursor);
	}
	if (op_tab[cursor->op_code].args_count >= 3)
	{
		args_size += vm->size[args_code.arg2];
		arg[2].num = get_arg(args_code.arg3, args_size, vm->arena, cursor);
	}
}

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
	print_command(args_code, vm, cursor);
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
