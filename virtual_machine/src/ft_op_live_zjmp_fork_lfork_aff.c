/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op_live_zjmp_fork_lfork_aff.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 20:20:34 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/15 20:20:36 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	live(t_data *data, t_cur *cursor)
{
	t_int			arg;
	int8_t			args_size;
	t_types_code	args_code;

	args_code.num = 0;
	args_size = 1;
	arg.num = get_arg(DIR_CODE, args_size, data->vm.arena, cursor);
	args_size += data->size[DIR_CODE];
	cursor->byte_to_next_op = args_size;
	if (ft_bit_check(data->v_flag, 2) && data->web_flag == 0)
		flag_v4(&arg, args_code, data, cursor);
	++data->vm.number_of_live;
	cursor->cycle_of_last_live = data->vm.cycle + data->vm.cycle_from_start;
	arg.num *= -1;
	if (arg.num >= data->vm.min_player_id && arg.num <= data->vm.num_of_players)
	{
		data->vm.last_player_id = arg.num;
		if (ft_bit_check(data->v_flag, 0))
			flag_v1(data, arg.num);
		if (data->l_flag == 0 && data->o_flag == 0)
			ft_bprintf(&data->fstr,
					"A process shows that player %d (%s) is alive\n",
					arg.num, data->player[arg.num - 1].name);
	}
}

void	zjmp(t_data *data, t_cur *cursor)
{
	t_int			arg;
	int8_t			args_size;
	t_types_code	args_code;

	args_code.num = 0;
	args_size = 1;
	arg.num = get_arg(DIR_CODE, args_size, data->vm.arena, cursor);
	args_size += data->size[DIR_CODE];
	if (cursor->carry == 1)
	{
		cursor->byte_to_next_op = arg.num % IDX_MOD;
		if (cursor->pc + cursor->byte_to_next_op < 0)
			cursor->byte_to_next_op = MEM_SIZE + cursor->byte_to_next_op;
	}
	else
		cursor->byte_to_next_op = args_size;
	if (ft_bit_check(data->v_flag, 2) && data->web_flag == 0)
		flag_v4(&arg, args_code, data, cursor);
}

void	fork_cw(t_data *data, t_cur *cursor)
{
	t_int			arg;
	int8_t			args_size;
	t_types_code	args_code;
	t_cur			*new_cur;
	int				num_player;

	args_code.num = 0;
	args_size = 1;
	arg.num = get_arg(DIR_CODE, args_size, data->vm.arena, cursor);
	args_size += data->size[DIR_CODE];
	cursor->byte_to_next_op = args_size;
	if (ft_bit_check(data->v_flag, 2) && data->web_flag == 0)
		flag_v4(&arg, args_code, data, cursor);
	new_cur = ft_copy_cursor(data, cursor);
	new_cur->pc = (cursor->pc + (arg.num % IDX_MOD)) % MEM_SIZE;
	if (new_cur->pc < 0)
		new_cur->pc += MEM_SIZE;
	if (data->web_flag)
	{
		num_player = cursor->reg[0] * -1;
		if (num_player > 0 && num_player <= data->vm.num_of_players)
			++data->web.curs[num_player - 1][0];
		data->web.change[new_cur->pc] = data->web.arena[new_cur->pc] + 1000;
	}
}

void	lfork_cw(t_data *data, t_cur *cursor)
{
	t_int			arg;
	int8_t			args_size;
	t_types_code	args_code;
	t_cur			*new_cur;
	int				num_player;

	args_code.num = 0;
	args_size = 1;
	arg.num = get_arg(DIR_CODE, args_size, data->vm.arena, cursor);
	args_size += data->size[DIR_CODE];
	cursor->byte_to_next_op = args_size;
	if (ft_bit_check(data->v_flag, 2) && data->web_flag == 0)
		flag_v4(&arg, args_code, data, cursor);
	new_cur = ft_copy_cursor(data, cursor);
	new_cur->pc = (cursor->pc + arg.num) % MEM_SIZE;
	if (new_cur->pc < 0)
		new_cur->pc += MEM_SIZE;
	if (data->web_flag)
	{
		num_player = cursor->reg[0] * -1;
		if (num_player > 0 && num_player <= data->vm.num_of_players)
			++data->web.curs[num_player - 1][0];
		data->web.change[new_cur->pc] = data->web.arena[new_cur->pc] + 1000;
	}
}

void	aff(t_data *data, t_cur *cursor)
{
	t_int			arg;
	int8_t			args_size;
	t_types_code	args_code;

	args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
	args_size = 2;
	arg.num = get_arg(args_code.a.arg1, args_size, data->vm.arena, cursor);
	args_size += data->size[args_code.a.arg1];
	cursor->byte_to_next_op = args_size;
	arg.num = cursor->reg[arg.num - 1];
	if ((char)arg.num == 0)
		ft_bprintf(&data->fstr, "Aff: \n");
	else
		ft_bprintf(&data->fstr, "Aff: %c\n", (char)arg.num);
}
