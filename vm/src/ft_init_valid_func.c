/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_valid_func.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:27:59 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/25 16:28:00 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static uint8_t	valid_zero(uint8_t arg_type)
{
	t_bits	arg_bits;

	arg_bits.num = arg_type;
	if (!arg_bits.bit3)
		return (0);
	return (1);
}

static uint8_t	valid_reg(uint8_t arg_type /*в таблице*/)
{
	t_bits	arg_bits;

	arg_bits.num = arg_type;
	if (arg_bits.bit0)
		return (0);
	return (1);
}

static uint8_t	valid_dir(uint8_t arg_type)
{
	t_bits	arg_bits;

	arg_bits.num = arg_type;
	if (arg_bits.bit1)
		return (0);
	return (1);
}

static uint8_t	valid_ind(uint8_t arg_type)
{
	t_bits	arg_bits;

	arg_bits.num = arg_type;
	if (arg_bits.bit2)
		return (0);
	return (1);
}

void			ft_init_valid_func(uint8_t (**valid) (uint8_t))
{
	valid[0] = valid_zero;
	valid[REG_CODE] = valid_reg;
	valid[DIR_CODE] = valid_dir;
	valid[IND_CODE] = valid_ind;
}
