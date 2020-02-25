/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op_ld_ldi_lld_lldi.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 20:25:23 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/15 20:25:24 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ld(t_data *data, t_cur *cursor)
{
	t_int			arg[2];
	t_types_code	args_code;

	args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
	get_args(arg, args_code, cursor, data);
	if (ft_bit_check(data->v_flag, 2) && data->web_flag == 0)
		flag_v4(arg, args_code, data, cursor);
	if (args_code.a.arg1 == IND_CODE)
	{
		arg[0].num %= IDX_MOD;
		arg[0].num = get_ind_value(arg[0], cursor, data);
	}
	cursor->reg[arg[1].num - 1] = arg[0].num;
	cursor->carry = (cursor->reg[arg[1].num - 1] == 0) ? 1 : 0;
}

void	ldi(t_data *data, t_cur *cursor)
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
		arg[0].num = get_ind_value(arg[0], cursor, data);
	if (args_code.a.arg2 == REG_CODE)
		arg[1].num = cursor->reg[arg[1].num - 1];
	else if (args_code.a.arg2 == IND_CODE)
		arg[1].num = get_ind_value(arg[1], cursor, data);
	arg[0].num = (arg[0].num + arg[1].num) % IDX_MOD;
	arg[0].num = get_ind_value(arg[0], cursor, data);
	cursor->reg[arg[2].num - 1] = arg[0].num;
}

void	lld(t_data *data, t_cur *cursor)
{
	t_int			arg[2];
	t_types_code	args_code;

	args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
	get_args(arg, args_code, cursor, data);
	if (ft_bit_check(data->v_flag, 2) && data->web_flag == 0)
		flag_v4(arg, args_code, data, cursor);
	if (args_code.a.arg1 == IND_CODE)
		arg[0].num = get_ind_value(arg[0], cursor, data);
	cursor->reg[arg[1].num - 1] = arg[0].num;
	cursor->carry = (cursor->reg[arg[1].num - 1] == 0) ? 1 : 0;
}

void	lldi(t_data *data, t_cur *cursor)
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
		arg[0].num = get_ind_value(arg[0], cursor, data);
	if (args_code.a.arg2 == REG_CODE)
		arg[1].num = cursor->reg[arg[1].num - 1];
	else if (args_code.a.arg2 == IND_CODE)
		arg[1].num = get_ind_value(arg[1], cursor, data);
	arg[0].num = arg[0].num + arg[1].num;
	arg[0].num = get_ind_value(arg[0], cursor, data);
	cursor->reg[arg[2].num - 1] = arg[0].num;
	cursor->carry = (cursor->reg[arg[2].num - 1] == 0) ? 1 : 0;
}
