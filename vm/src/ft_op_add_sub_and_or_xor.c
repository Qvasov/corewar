/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op_add_sub_and_or_xor.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 20:35:18 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/15 20:35:20 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	add(t_data *data, t_cur *cursor)
{
	t_int			arg[3];
	t_types_code	args_code;

	args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
	get_args(arg, args_code, cursor, data);
	if (ft_bit_check(data->v_flag, 2) && data->web_flag == 0)
		flag_v4(arg, args_code, data, cursor);
	cursor->reg[arg[2].num - 1] = cursor->reg[arg[0].num - 1] +
			cursor->reg[arg[1].num - 1];
	cursor->carry = (cursor->reg[arg[2].num - 1] == 0) ? 1 : 0;
}

void	sub(t_data *data, t_cur *cursor)
{
	t_int			arg[3];
	t_types_code	args_code;

	args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
	get_args(arg, args_code, cursor, data);
	if (ft_bit_check(data->v_flag, 2) && data->web_flag == 0)
		flag_v4(arg, args_code, data, cursor);
	cursor->reg[arg[2].num - 1] = cursor->reg[arg[0].num - 1] -
			cursor->reg[arg[1].num - 1];
	cursor->carry = (cursor->reg[arg[2].num - 1] == 0) ? 1 : 0;
}

void	and(t_data *data, t_cur *cursor)
{
	t_int			arg[3];
	t_types_code	args_code;

	args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
	get_args(arg, args_code, cursor, data);
	if (ft_bit_check(data->v_flag, 2) && data->web_flag == 0)
		flag_v4(arg, args_code, data, cursor);
	if (args_code.a.arg1 == REG_CODE)
		arg[0].num = cursor->reg[arg[0].num - 1];
	else if (args_code.a.arg1 == IND_CODE)
	{
		arg[0].num %= IDX_MOD;
		arg[0].num = get_ind_value(arg[0], cursor, data);
	}
	if (args_code.a.arg2 == REG_CODE)
		arg[1].num = cursor->reg[arg[1].num - 1];
	else if (args_code.a.arg2 == IND_CODE)
	{
		arg[1].num %= IDX_MOD;
		arg[1].num = get_ind_value(arg[1], cursor, data);
	}
	cursor->reg[arg[2].num - 1] = arg[0].num & arg[1].num;
	cursor->carry = (cursor->reg[arg[2].num - 1] == 0) ? 1 : 0;
}

void	or(t_data *data, t_cur *cursor)
{
	t_int			arg[3];
	t_types_code	args_code;

	args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
	get_args(arg, args_code, cursor, data);
	if (ft_bit_check(data->v_flag, 2) && data->web_flag == 0)
		flag_v4(arg, args_code, data, cursor);
	if (args_code.a.arg1 == REG_CODE)
		arg[0].num = cursor->reg[arg[0].num - 1];
	else if (args_code.a.arg1 == IND_CODE)
	{
		arg[0].num %= IDX_MOD;
		arg[0].num = get_ind_value(arg[0], cursor, data);
	}
	if (args_code.a.arg2 == REG_CODE)
		arg[1].num = cursor->reg[arg[1].num - 1];
	else if (args_code.a.arg2 == IND_CODE)
	{
		arg[1].num %= IDX_MOD;
		arg[1].num = get_ind_value(arg[1], cursor, data);
	}
	cursor->reg[arg[2].num - 1] = arg[0].num | arg[1].num;
	cursor->carry = (cursor->reg[arg[2].num - 1] == 0) ? 1 : 0;
}

void	xor(t_data *data, t_cur *cursor)
{
	t_int			arg[3];
	t_types_code	args_code;

	args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
	get_args(arg, args_code, cursor, data);
	if (ft_bit_check(data->v_flag, 2) && data->web_flag == 0)
		flag_v4(arg, args_code, data, cursor);
	if (args_code.a.arg1 == REG_CODE)
		arg[0].num = cursor->reg[arg[0].num - 1];
	else if (args_code.a.arg1 == IND_CODE)
	{
		arg[0].num %= IDX_MOD;
		arg[0].num = get_ind_value(arg[0], cursor, data);
	}
	if (args_code.a.arg2 == REG_CODE)
		arg[1].num = cursor->reg[arg[1].num - 1];
	else if (args_code.a.arg2 == IND_CODE)
	{
		arg[1].num %= IDX_MOD;
		arg[1].num = get_ind_value(arg[1], cursor, data);
	}
	cursor->reg[arg[2].num - 1] = arg[0].num ^ arg[1].num;
	cursor->carry = (cursor->reg[arg[2].num - 1] == 0) ? 1 : 0;
}
