/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_bigint_shiftl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 20:27:41 by laleta            #+#    #+#             */
/*   Updated: 2019/06/21 02:29:49 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_dragon4.h"

static inline void	bigint_shiftl_aux(t_bigint **res, uint32_t shift_block,
															uint32_t shift_bit)
{
	uint32_t		i;
	uint32_t		high_bit;
	uint32_t		low_bit;

	(*res)->length = (*res)->length + shift_block + 1;
	high_bit = 0;
	i = (*res)->length - 1;
	low_bit = (*res)->block[i] >> (32 - shift_bit);
	while (i > 0)
	{
		(*res)->block[i + 1 + shift_block] = high_bit | low_bit;
		high_bit = (*res)->block[i] << shift_bit;
		--i;
		low_bit = (*res)->block[i] >> (32 - shift_bit);
	}
	(*res)->block[i + shift_block + 1] = high_bit | low_bit;
	(*res)->block[i + shift_block] = (*res)->block[i] << shift_bit;
	i = 0;
	while (i < shift_block)
		(*res)->block[i++] = 0;
	if ((*res)->block[(*res)->length - 1] == 0)
		--(*res)->length;
}

void				bigint_shiftl(t_bigint *res, uint32_t shift)
{
	uint32_t			shift_block;
	uint32_t			shift_bit;
	uint32_t			i;

	shift_block = shift / 32;
	shift_bit = shift % 32;
	if (shift_bit == 0)
	{
		i = res->length;
		while ((int)--i >= 0)
			res->block[i + shift_block] = res->block[i];
		i = 0;
		while (i < shift_block)
			res->block[i++] = 0;
		res->length += shift_block;
	}
	else
		bigint_shiftl_aux(&res, shift_block, shift_bit);
}
