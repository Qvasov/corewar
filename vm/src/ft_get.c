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

int		get_ind_value(t_int arg, t_cur *cursor, uint8_t *arena)
{
	int32_t	addr;

	addr = (cursor->pc + arg.num) % MEM_SIZE;
	if (addr < 0)
		addr = MEM_SIZE + (addr % MEM_SIZE);
	arg.byte[3]= arena[addr % MEM_SIZE];
	arg.byte[2]= arena[(addr + 1) % MEM_SIZE];
	arg.byte[1]= arena[(addr + 2) % MEM_SIZE];
	arg.byte[0]= arena[(addr + 3) % MEM_SIZE];
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
		j = (arg_code == DIR_CODE && !op_tab[cursor->op_code].dir_size) ? 3 : 1;
		while (++i <= j)
			ret.byte[j - i] = arena[(cursor->pc + arg_pos + i) % MEM_SIZE];
		if (j == 1)
			ret.num = (int16_t)ret.num;
	}
	return (ret.num);
}
