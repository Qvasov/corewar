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
	int8_t			args_size;
	t_types_code	args_code;

	args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg2];
	cursor->byte_to_next_op = args_size;

	if (data->v_flag.bit2 && data->web_flag == 0)
		ft_print_command(arg, args_code, &data->vm, cursor);

	if (args_code.arg1 == IND_CODE)
	{
		arg[0].num %= IDX_MOD;
		arg[0].num = get_ind_value(arg[0], cursor, data->vm.arena); // получение числа по адресу
	}
	cursor->reg[arg[1].num - 1] = arg[0].num;
	cursor->carry = (cursor->reg[arg[1].num - 1] == 0) ? 1 : 0;
}

void	ldi(t_data *data, t_cur *cursor)
{
	t_int			arg[3];
	int8_t			args_size;
	t_types_code	args_code;

	args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg2];
	arg[2].num = get_arg(args_code.arg3, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg3];
	cursor->byte_to_next_op = args_size;

	if (data->v_flag.bit2 && data->web_flag == 0)
		ft_print_command(arg, args_code, &data->vm, cursor);

	if (args_code.arg1 == REG_CODE)
		arg[0].num = cursor->reg[arg[0].num - 1];
	else if (args_code.arg1 == IND_CODE)
		arg[0].num = get_ind_value(arg[0], cursor, data->vm.arena);
	if (args_code.arg2 == REG_CODE)
		arg[1].num = cursor->reg[arg[1].num - 1];
	else if (args_code.arg2 == IND_CODE)
		arg[1].num = get_ind_value(arg[1], cursor, data->vm.arena);
	arg[0].num = (arg[0].num + arg[1].num) % IDX_MOD;
	arg[0].num = get_ind_value(arg[0], cursor, data->vm.arena);
	cursor->reg[arg[2].num - 1] = arg[0].num;
}

void	lld(t_data *data, t_cur *cursor)
{
	t_int	arg[2];
	int8_t	args_size;
	t_types_code	args_code;

	args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg2];
	cursor->byte_to_next_op = args_size;

	if (data->v_flag.bit2 && data->web_flag == 0)
		ft_print_command(arg, args_code, &data->vm, cursor);

	if (args_code.arg1 == IND_CODE) //получение числа по адресу
		arg[0].num = get_ind_value(arg[0], cursor, data->vm.arena);
	cursor->reg[arg[1].num - 1] = arg[0].num;
	cursor->carry = (cursor->reg[arg[1].num - 1] == 0) ? 1 : 0;

}

void	lldi(t_data *data, t_cur *cursor)
{
	t_int			arg[3];
	int8_t			args_size;
	t_types_code	args_code;

	args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg2];
	arg[2].num = get_arg(args_code.arg3, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg3];
	cursor->byte_to_next_op = args_size;

	if (data->v_flag.bit2 && data->web_flag == 0)
		ft_print_command(arg, args_code, &data->vm, cursor);

	if (args_code.arg1 == REG_CODE)
		arg[0].num = cursor->reg[arg[0].num - 1];
	else if (args_code.arg1 == IND_CODE)
		arg[0].num = get_ind_value(arg[0], cursor, data->vm.arena);
	if (args_code.arg2 == REG_CODE)
		arg[1].num = cursor->reg[arg[1].num - 1];
	else if (args_code.arg2 == IND_CODE)
		arg[1].num = get_ind_value(arg[1], cursor, data->vm.arena);
	arg[0].num = arg[0].num + arg[1].num;
	arg[0].num = get_ind_value(arg[0], cursor, data->vm.arena);
	cursor->reg[arg[2].num - 1] = arg[0].num;
	cursor->carry = (cursor->reg[arg[2].num - 1] == 0) ? 1 : 0;
}
