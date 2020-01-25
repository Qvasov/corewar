/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_valid_func.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:27:59 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/25 16:28:00 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int8_t	valid_zero(int8_t arg_types)
{
	t_bits	arg_bits;

	arg_bits.num = arg_types;
	if (!arg_bits.bit3)
		return (0);
	return (1);
}

static int8_t	valid_reg(int8_t arg_types /*в таблице*/)
{
	t_bits	arg_bits;

	arg_bits.num = arg_types;
	if (arg_bits.bit0)
		return (0);
	return (1);
}

static int8_t	valid_dir(int8_t arg_types)
{
	t_bits	arg_bits;

	arg_bits.num = arg_types;
	if (arg_bits.bit1)
		return (0);
	return (1);
}

static int8_t	valid_ind(int8_t arg_types)
{
	t_bits	arg_bits;

	arg_bits.num = arg_types;
	if (arg_bits.bit2)
		return (0);
	return (1);
}

void			ft_set_valid_func(int8_t (**type) (int8_t))
{
	type[0] = valid_zero;
	type[REG_CODE] = valid_reg;
	type[DIR_CODE] = valid_dir;
	type[IND_CODE] = valid_ind;
}
