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
	t_int	arg[3];
	int8_t	args_size;
	t_types_code	args_code;

	args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, data->vm.arena, cursor);
	args_size += data->size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, data->vm.arena, cursor);
	args_size += data->size[args_code.arg2];
	arg[2].num = get_arg(args_code.arg3, args_size, data->vm.arena, cursor);
	args_size += data->size[args_code.arg3];
	cursor->byte_to_next_op = args_size;

	if (ft_bit_check(data->v_flag, 2) && data->web_flag == 0)
		ft_flag_v4(arg, args_code, &data->vm, cursor);

	cursor->reg[arg[2].num - 1] = cursor->reg[arg[0].num - 1] + cursor->reg[arg[1].num - 1];
	cursor->carry = (cursor->reg[arg[2].num - 1] == 0) ? 1 : 0;
}

void	sub(t_data *data, t_cur *cursor)
{
	t_int	arg[3];
	int8_t	args_size;
	t_types_code	args_code;

	args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, data->vm.arena, cursor);
	args_size += data->size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, data->vm.arena, cursor);
	args_size += data->size[args_code.arg2];
	arg[2].num = get_arg(args_code.arg3, args_size, data->vm.arena, cursor);
	args_size += data->size[args_code.arg3];
	cursor->byte_to_next_op = args_size;

	if (ft_bit_check(data->v_flag, 2) && data->web_flag == 0)
		ft_flag_v4(arg, args_code, &data->vm, cursor);

	cursor->reg[arg[2].num - 1] = cursor->reg[arg[0].num - 1] - cursor->reg[arg[1].num - 1];
	cursor->carry = (cursor->reg[arg[2].num - 1] == 0) ? 1 : 0;
}

void	and(t_data *data, t_cur *cursor)
{
	t_int	arg[3];
	int8_t	args_size;
	t_types_code	args_code;

	args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, data->vm.arena, cursor);
	args_size += data->size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, data->vm.arena, cursor);
	args_size += data->size[args_code.arg2];
	arg[2].num = get_arg(args_code.arg3, args_size, data->vm.arena, cursor);
	args_size += data->size[args_code.arg3];
	cursor->byte_to_next_op = args_size;

	if (ft_bit_check(data->v_flag, 2) && data->web_flag == 0)
		ft_flag_v4(arg, args_code, &data->vm, cursor);

	if (args_code.arg1 == REG_CODE)
		arg[0].num = cursor->reg[arg[0].num - 1];
	else if (args_code.arg1 == IND_CODE)
		arg[0].num = get_ind_value(arg[0], cursor, data->vm.arena) % IDX_MOD;
	if (args_code.arg2 == REG_CODE)
		arg[1].num = cursor->reg[arg[1].num - 1];
	else if (args_code.arg2 == IND_CODE)
		arg[1].num = get_ind_value(arg[1], cursor, data->vm.arena) % IDX_MOD;
	cursor->reg[arg[2].num - 1] = arg[0].num & arg[1].num;
	cursor->carry = (cursor->reg[arg[2].num - 1] == 0) ? 1 : 0;
}

void	or(t_data *data, t_cur *cursor)
{
	t_int	arg[3];
	int8_t	args_size;
	t_types_code	args_code;

	args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, data->vm.arena, cursor);
	args_size += data->size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, data->vm.arena, cursor);
	args_size += data->size[args_code.arg2];
	arg[2].num = get_arg(args_code.arg3, args_size, data->vm.arena, cursor);
	args_size += data->size[args_code.arg3];
	cursor->byte_to_next_op = args_size;

	if (ft_bit_check(data->v_flag, 2) && data->web_flag == 0)
		ft_flag_v4(arg, args_code, &data->vm, cursor);

	if (args_code.arg1 == REG_CODE)
		arg[0].num = cursor->reg[arg[0].num - 1];
	else if (args_code.arg1 == IND_CODE)
		arg[0].num = get_ind_value(arg[0], cursor, data->vm.arena) % IDX_MOD;
	if (args_code.arg2 == REG_CODE)
		arg[1].num = cursor->reg[arg[1].num - 1];
	else if (args_code.arg2 == IND_CODE)
		arg[1].num = get_ind_value(arg[1], cursor, data->vm.arena) % IDX_MOD;
	cursor->reg[arg[2].num - 1] = arg[0].num | arg[1].num;
	cursor->carry = (cursor->reg[arg[2].num - 1] == 0) ? 1 : 0;
}

void	xor(t_data *data, t_cur *cursor)
{
	t_int	arg[3];
	int8_t	args_size;
	t_types_code	args_code;

	args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, data->vm.arena, cursor);
	args_size += data->size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, data->vm.arena, cursor);
	args_size += data->size[args_code.arg2];
	arg[2].num = get_arg(args_code.arg3, args_size, data->vm.arena, cursor);
	args_size += data->size[args_code.arg3];
	cursor->byte_to_next_op = args_size;

	if (ft_bit_check(data->v_flag, 2) && data->web_flag == 0)
		ft_flag_v4(arg, args_code, &data->vm, cursor);

	if (args_code.arg1 == REG_CODE)
		arg[0].num = cursor->reg[arg[0].num - 1];
	else if (args_code.arg1 == IND_CODE)
		arg[0].num = get_ind_value(arg[0], cursor, data->vm.arena) % IDX_MOD;
	if (args_code.arg2 == REG_CODE)
		arg[1].num = cursor->reg[arg[1].num - 1];
	else if (args_code.arg2 == IND_CODE)
		arg[1].num = get_ind_value(arg[1], cursor, data->vm.arena) % IDX_MOD;
	cursor->reg[arg[2].num - 1] = arg[0].num ^ arg[1].num;
	cursor->carry = (cursor->reg[arg[2].num - 1] == 0) ? 1 : 0;
}
