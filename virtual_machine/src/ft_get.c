/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:03:05 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/06 18:03:06 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_ind_value(t_int arg, t_cur *cursor, t_data *data)
{
	int32_t	addr;
	int		i;
	int		size;

	addr = (cursor->pc + arg.num) % MEM_SIZE;
	if (addr < 0)
		addr = MEM_SIZE + (addr % MEM_SIZE);
	size = (cursor->op == LLD && data->o_flag) ? 1 : 3;
	i = -1;
	while (++i <= size)
		arg.byte[size - i] = data->vm.arena[(addr + i) % MEM_SIZE];
	if (size == 1)
		arg.num = (int16_t)arg.num;
	return (arg.num);
}

int		get_arg(uint8_t arg_code, int8_t arg_pos, uint8_t *arena, t_cur *cursor)
{
	t_int	ret;
	int8_t	i;
	int8_t	j;

	ret.num = 0;
	if (arg_code == REG_CODE)
		ret.num = arena[(cursor->pc + arg_pos) % MEM_SIZE];
	else if (arg_code == DIR_CODE || arg_code == IND_CODE)
	{
		i = -1;
		j = (arg_code == DIR_CODE && !g_op[cursor->op].dir_size) ? 3 : 1;
		while (++i <= j)
			ret.byte[j - i] = arena[(cursor->pc + arg_pos + i) % MEM_SIZE];
		if (j == 1)
			ret.num = (int16_t)ret.num;
	}
	return (ret.num);
}

void	get_args(t_int *arg, t_types_code args_code, t_cur *cursor,
		t_data *data)
{
	int8_t	args_size;
	int		i;

	args_size = 2;
	i = -1;
	if (++i < g_op[cursor->op].args_count)
	{
		arg[i].num = get_arg(args_code.a.arg1, args_size, data->vm.arena,
				cursor);
		args_size += data->size[args_code.a.arg1];
	}
	if (++i < g_op[cursor->op].args_count)
	{
		arg[i].num = get_arg(args_code.a.arg2, args_size, data->vm.arena,
				cursor);
		args_size += data->size[args_code.a.arg2];
	}
	if (++i < g_op[cursor->op].args_count)
	{
		arg[i].num = get_arg(args_code.a.arg3, args_size, data->vm.arena,
				cursor);
		args_size += data->size[args_code.a.arg3];
	}
	cursor->byte_to_next_op = args_size;
}
