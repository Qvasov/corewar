/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_flag_v4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:23:08 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/19 21:23:16 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void print_additional_info(t_int *arg, t_cur *cursor, t_data *data)
{
	if (cursor->op_code == LDI)
		ft_bprintf(&data->fstr, "\n %5s | -> load from %d + %d = %d (with pc and mod %d)\n",
				  "", arg[0].num, arg[1].num, arg[0].num + arg[1].num,
				  (cursor->pc + (arg[0].num + arg[1].num) % IDX_MOD));
	else if (cursor->op_code == STI)
		ft_bprintf(&data->fstr, "\n %5s | -> store to %d + %d = %d (with pc and mod %d)\n",
				  "", arg[1].num, arg[2].num, arg[1].num + arg[2].num,
				  cursor->pc + (arg[1].num + arg[2].num) % IDX_MOD);
	else if (cursor->op_code == FORK)
		ft_bprintf(&data->fstr, " (%d)\n", ((arg[0].num % IDX_MOD) + cursor->pc)/* % MEM_SIZE*/);
	else if (cursor->op_code == LLDI)
		ft_bprintf(&data->fstr, "\n %5s | -> load from %d + %d = %d (with pc %d)\n",
				  "", arg[0].num, arg[1].num, arg[0].num + arg[1].num,
				  cursor->pc + (arg[0].num + arg[1].num));
	else if (cursor->op_code == LFORK)
		ft_bprintf(&data->fstr, " (%d)\n", arg[0].num + cursor->pc);
	else
		ft_bprintf(&data->fstr, "\n");
}

static void	print_value(uint8_t arg_code, t_int *arg, t_data *data, t_cur *cursor)
{
	if (!(g_op[cursor->op_code].args_type_code))
	{
		if (cursor->op_code == ZJMP)
			(cursor->carry) ? ft_bprintf(&data->fstr, " %d OK", arg->num) :
							ft_bprintf(&data->fstr, " %d FAILED", arg->num);
		else
			ft_bprintf(&data->fstr, " %d", arg->num);
		return ;
	}
	if (arg_code == REG_CODE)
		ft_bprintf(&data->fstr, " r%d", arg->num);
	else if (arg_code == DIR_CODE)
		ft_bprintf(&data->fstr, " %d", arg->num);
	else if (arg_code == IND_CODE)
	{
		if (cursor->op_code == LD || cursor->op_code == LDI ||
			cursor->op_code == LLD || cursor->op_code == LLDI ||
			cursor->op_code == STI || cursor->op_code == AND ||
			cursor->op_code == OR || cursor->op_code == XOR)
			arg->num = get_ind_value(*arg, cursor, data);
		ft_bprintf(&data->fstr, " %d", arg->num);
	}
}

static void flag_v4_arg2(t_int *arg, t_types_code args_code, t_data *data, t_cur *cursor)
{
	if (args_code.a.arg2 == REG_CODE && (cursor->op_code == ST ||
		(cursor->op_code >= AND && cursor->op_code <= XOR) ||
		cursor->op_code == LDI || cursor->op_code == STI || cursor->op_code == LLDI))
	{
		if (!(cursor->op_code == ST && data->o_flag == 1))				//обсудить для st rx,rx как выводить второе число. В оригинальной vm выводит просто номер регистра без r
			arg->num = cursor->reg[arg->num - 1];
		ft_bprintf(&data->fstr, " %d", arg->num);
	}
	else
		print_value(args_code.a.arg2, arg, data, cursor);
}

static void flag_v4_arg3(t_int *arg, t_types_code args_code, t_data *data, t_cur *cursor)
{
	if (args_code.a.arg3 == REG_CODE && (cursor->op_code == STI))
	{
		arg->num = cursor->reg[arg->num - 1];
		ft_bprintf(&data->fstr, " %d", arg->num);
	}
	else
		print_value(args_code.a.arg3, arg, data, cursor);
}

void		flag_v4(const t_int *args, t_types_code args_code, t_data *data, t_cur *cursor)
{
	t_int	arg[3];

	if (g_op[cursor->op_code].args_type_code && args_code.num == 0)
		return ;
	ft_bprintf(&data->fstr, "P %4d | %s", cursor->id, g_op[cursor->op_code].name);
	arg[0] = args[0];
	if (args_code.a.arg1 == REG_CODE &&
		(cursor->op_code == LDI || cursor->op_code == LLDI ||
		(cursor->op_code >= AND && cursor->op_code <= XOR)))
	{
		arg[0].num = cursor->reg[arg[0].num - 1];
		ft_bprintf(&data->fstr, " %d", arg[0].num);
	}
	else
		print_value(args_code.a.arg1, &arg[0], data, cursor);
	if (g_op[cursor->op_code].args_count >= 2)
	{
		arg[1] = args[1];
		flag_v4_arg2(&arg[1], args_code, data, cursor);
	}
	if (g_op[cursor->op_code].args_count >= 3)
	{
		arg[2] = args[2];
		flag_v4_arg3(&arg[2], args_code, data, cursor);
	}
	print_additional_info(arg, cursor, data);
}
