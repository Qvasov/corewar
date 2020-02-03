/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 19:25:21 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/01 19:25:22 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_value(uint8_t arg_code, t_int arg, t_vm *vm, t_cur *cursor)
{
	if (!(op_tab[cursor->op_code].args_type_code))
	{
		if (cursor->op_code == 0x09)
			(cursor->carry) ? ft_printf(" %d OK", arg.num %= IDX_MOD) :
			ft_printf(" %d FAILED", arg.num %= IDX_MOD);
		else
			ft_printf(" %d", arg.num);
		return ;
	}
	if (arg_code == REG_CODE)
		ft_printf(" r%d", arg.num);
	else if (arg_code == DIR_CODE)
		ft_printf(" %d", arg.num);
	else if (arg_code == IND_CODE)
	{
		if (cursor->op_code == 0x02)
			arg.num = get_ind_value(arg, cursor, vm->arena);
		ft_printf(" %d", arg.num);
	}
}

static void print_additional_info(t_int *arg, t_cur *cursor)
{
	if (cursor->op_code == 0x0a)
	{
		ft_printf("\n %5s | -> load from %d + %d = %d (with pc and mod %d)\n",
				  "", arg[0].num, arg[1].num, arg[0].num + arg[1].num,
				  (cursor->pc + (arg[0].num + arg[1].num) % IDX_MOD));
	}
	else if (cursor->op_code == 0x0b)
	{
		ft_printf("\n %5s | -> store to %d + %d = %d (with pc and mod %d)\n",
				  "", arg[1].num, arg[2].num, arg[1].num + arg[2].num,
				  cursor->pc + (arg[1].num + arg[2].num) % IDX_MOD);
	}
	else if (cursor->op_code == 0x0c || cursor->op_code == 0x0f)
	{
		arg[0].num = arg[0].num + cursor->pc;
		(arg[0].num < 0) ? arg[0].num += MEM_SIZE : 0;
		ft_printf(" (%d)\n", arg[0].num);
	}
	else
		ft_printf("\n");
}

void ft_print_commands(t_vm *vm, t_cur *cursor)
{
	t_int			arg[3];
	int8_t			args_size;
	t_types_code	args_code;

	args_code.num = 0;
	args_size = 1;
	if (op_tab[cursor->op_code].args_type_code)
	{
		args_code.num = vm->arena[(cursor->pc + 1) % MEM_SIZE];
		++args_size;
		arg[0].num = get_arg(args_code.arg1, args_size, vm->arena, cursor);
	}
	else
		arg[0].num = get_arg(op_tab[cursor->op_code].arg_type[0], args_size, vm->arena, cursor);

	if (op_tab[cursor->op_code].args_type_code && args_code.num == 0)
		return ;
	ft_printf("P%5d | %s", cursor->id, op_tab[cursor->op_code].name);
	if (args_code.arg1 == REG_CODE &&
		((cursor->op_code >= 0x06 && cursor->op_code <= 0x08) ||
		cursor->op_code == 0x0a))
	{
		arg[0].num = cursor->reg[arg[0].num - 1];
		ft_printf(" %d", arg[0].num);
	}
	else
		print_value(args_code.arg1, arg[0], vm, cursor);

	if (op_tab[cursor->op_code].args_count >= 2)
	{
		args_size += vm->size[args_code.arg1];
		arg[1].num = get_arg(args_code.arg2, args_size, vm->arena, cursor);
		if (args_code.arg2 == REG_CODE &&
			((cursor->op_code >= 0x06 && cursor->op_code <= 0x08) ||
			 cursor->op_code == 0x0a || cursor->op_code == 0x0b))
		{
			arg[1].num = cursor->reg[arg[1].num - 1];
			ft_printf(" %d", arg[1].num);
		}
		else
			print_value(args_code.arg2, arg[1], vm, cursor);
	}

	if (op_tab[cursor->op_code].args_count >= 3)
	{
		args_size += vm->size[args_code.arg2];
		arg[2].num = get_arg(args_code.arg3, args_size, vm->arena, cursor);
		if (args_code.arg3 == REG_CODE &&
			(cursor->op_code == 0x0b))
		{
			arg[2].num = cursor->reg[arg[2].num - 1];
			ft_printf(" %d", arg[2].num);
		}
		else
			print_value(args_code.arg3, arg[2], vm, cursor);
	}
	print_additional_info(arg, cursor);
}
