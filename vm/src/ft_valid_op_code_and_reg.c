/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_op_code_and_reg.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 21:48:14 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/22 21:48:15 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	valid_number_reg(t_types_code args_code, t_cur *cursor, t_vm *vm,
		const int8_t *size)
{
	int16_t	reg_pos;

	if (1 <= g_op[cursor->op].args_count && args_code.a.arg1 == REG_CODE)
	{
		reg_pos = (cursor->pc + 2) % MEM_SIZE;
		if (!(vm->arena[reg_pos] >= 1 && vm->arena[reg_pos] <= 16))
			return (1);
	}
	if (2 <= g_op[cursor->op].args_count && args_code.a.arg2 == REG_CODE)
	{
		reg_pos = (cursor->pc + 2 + size[args_code.a.arg1]) % MEM_SIZE;
		if (!(vm->arena[reg_pos] >= 1 && vm->arena[reg_pos] <= 16))
			return (1);
	}
	if (3 <= g_op[cursor->op].args_count && args_code.a.arg3 == REG_CODE)
	{
		reg_pos = (cursor->pc + 2 + size[args_code.a.arg1] +
				size[args_code.a.arg2]) % MEM_SIZE;
		if (!(vm->arena[reg_pos] >= 1 && vm->arena[reg_pos] <= 16))
			return (1);
	}
	return (0);
}

int			ft_valid_op_code_and_reg(t_data *data, t_cur *cursor)
{
	t_types_code	args_code;

	if (g_op[cursor->op].args_type_code)
	{
		args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
		if (data->valid[args_code.a.arg1](0, cursor->op) ||
			data->valid[args_code.a.arg2](1, cursor->op) ||
			data->valid[args_code.a.arg3](2, cursor->op) ||
			data->valid[args_code.a.arg4](3, cursor->op) ||
			valid_number_reg(args_code, cursor, &data->vm, data->size))
			return (1);
	}
	return (0);
}
