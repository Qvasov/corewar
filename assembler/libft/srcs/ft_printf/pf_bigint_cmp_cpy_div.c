/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_bigint_cmp_cpy_div.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 02:20:16 by laleta            #+#    #+#             */
/*   Updated: 2019/06/21 02:40:06 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_dragon4.h"

void				bigint_cpy(t_bigint *dst, const t_bigint *src)
{
	uint32_t		length;
	uint32_t		*d;
	const uint32_t	*s;

	length = src->length;
	d = dst->block;
	s = src->block;
	while (s != src->block + length)
	{
		*d = *s;
		++d;
		++s;
	}
	dst->length = length;
}

int32_t				bigint_cmp(const t_bigint *bi1, const t_bigint *bi2)
{
	int32_t	i;
	int32_t	diff;

	diff = bi1->length - bi2->length;
	if (diff != 0)
		return (diff);
	i = bi1->length;
	while (--i >= 0)
	{
		if (bi1->block[i] == bi2->block[i])
			continue;
		else if (bi1->block[i] > bi2->block[i])
			return (1);
		else
			return (-1);
	}
	return (0);
}

static inline void	bigint_sub1(t_bigint **b1, const t_bigint *b2,
																uint32_t quot)
{
	uint64_t		borr;
	uint64_t		over;
	uint64_t		diff;
	uint64_t		mul;
	uint32_t		i;

	i = 0;
	borr = 0;
	over = 0;
	while (i < b2->length)
	{
		mul = (uint64_t)b2->block[i] * (uint64_t)quot + over;
		over = mul >> 32;
		diff = (uint64_t)(*b1)->block[i] - (mul & 0xFFFFFFFF) - borr;
		borr = (diff >> 32) & 1;
		(*b1)->block[i] = diff & 0xFFFFFFFF;
		++i;
	}
	while (i > 0 && (*b1)->block[i - 1] == 0)
		--i;
	(*b1)->length = i;
}

static inline void	bigint_sub2(t_bigint **b1, const t_bigint *b2)
{
	uint64_t		borr;
	uint64_t		diff;
	uint32_t		i;

	i = 0;
	borr = 0;
	while (i < b2->length)
	{
		diff = (uint64_t)(*b1)->block[i] - (uint64_t)b2->block[i] - borr;
		borr = (diff >> 32) & 1;
		(*b1)->block[i] = diff & 0xFFFFFFFF;
		++i;
	}
	while (i > 0 && (*b1)->block[i - 1] == 0)
		--i;
	(*b1)->length = i;
}

uint32_t			bigint_div(t_bigint *b1, const t_bigint *b2)
{
	uint32_t		quot;

	if (b1->length < b2->length)
		return (0);
	quot = (*(b1->block + b2->length - 1)) /
			(*(b2->block + b2->length - 1) + 1);
	if (quot != 0)
		bigint_sub1(&b1, b2, quot);
	if (bigint_cmp(b1, b2) >= 0)
	{
		++quot;
		bigint_sub2(&b1, b2);
	}
	return (quot);
}
