/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_valid_func.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:20:00 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/25 14:20:01 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static uint8_t	valid_zero(uint8_t i, uint8_t op)
{
	t_bits	arg_bits;

	if (i < g_op[op].args_count)
	{
		arg_bits.num = g_op[op].arg_type[i];
		if (arg_bits.b.bit3)
			return (0);
		else
			return (1);
	}
	return (0);
}

static uint8_t	valid_reg(uint8_t i, uint8_t op)
{
	t_bits	arg_bits;

	if (i < g_op[op].args_count)
	{
		arg_bits.num = g_op[op].arg_type[i];
		if (arg_bits.b.bit0)
			return (0);
		else
			return (1);
	}
	return (0);
}

static uint8_t	valid_dir(uint8_t i, uint8_t op)
{
	t_bits	arg_bits;

	if (i < g_op[op].args_count)
	{
		arg_bits.num = g_op[op].arg_type[i];
		if (arg_bits.b.bit1)
			return (0);
		else
			return (1);
	}
	return (0);
}

static uint8_t	valid_ind(uint8_t i, uint8_t op)
{
	t_bits	arg_bits;

	if (i < g_op[op].args_count)
	{
		arg_bits.num = g_op[op].arg_type[i];
		if (arg_bits.b.bit2)
			return (0);
		else
			return (1);
	}
	return (0);
}

void			ft_init_valid_func(uint8_t (**valid) (uint8_t, uint8_t))
{
	valid[0] = valid_zero;
	valid[REG_CODE] = valid_reg;
	valid[DIR_CODE] = valid_dir;
	valid[IND_CODE] = valid_ind;
}
