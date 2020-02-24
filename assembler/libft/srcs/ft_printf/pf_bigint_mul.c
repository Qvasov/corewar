/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_bigint_mul.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 02:22:34 by laleta            #+#    #+#             */
/*   Updated: 2019/06/24 02:07:32 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_dragon4.h"

static inline void	bigint_mul_aux(t_bigint *res, const t_bigint *l,
													uint64_t s_i, uint32_t i)
{
	uint64_t		over;
	uint64_t		mul;
	uint32_t		j;

	over = 0;
	j = 0;
	while (j < l->length)
	{
		mul = res->block[i + j] + l->block[j] * s_i + over;
		over = mul >> 32;
		res->block[i + j] = mul & 0xFFFFFFFF;
		++j;
	}
	res->block[i + j] = (uint32_t)(over & 0xFFFFFFFF);
}

void				bigint_mul(t_bigint *res, const t_bigint *b1,
															const t_bigint *b2)
{
	const t_bigint	*l;
	const t_bigint	*s;
	uint32_t		res_max;
	uint32_t		i;

	s = b1->length < b2->length ? b1 : b2;
	l = b1->length < b2->length ? b2 : b1;
	res_max = l->length + s->length;
	i = 0;
	while (i < res_max)
		res->block[i++] = 0;
	i = 0;
	while (i < s->length)
	{
		if (s->block[i] != 0)
			bigint_mul_aux(res, l, (uint64_t)s->block[i], i);
		++i;
	}
	res->length = res_max > 0 && res->block[res_max - 1] == 0 ?
														res_max - 1 : res_max;
}

void				bigint_mul_int(t_bigint *res, const t_bigint *b1,
																	uint32_t b2)
{
	uint32_t		over;
	uint32_t		i;
	uint64_t		mul;

	i = 0;
	over = 0;
	while (i < b1->length)
	{
		mul = (uint64_t)(b1->block[i]) * b2 + over;
		res->block[i] = (uint32_t)(mul & 0xFFFFFFFF);
		over = mul >> 32;
		++i;
	}
	res->length = over != 0 ? b1->length + 1 : b1->length;
	if (over != 0)
		res->block[i] = (uint32_t)over;
}

void				bigint_mul2(t_bigint *res)
{
	uint32_t		over;
	uint32_t		tmp;
	uint32_t		i;

	i = 0;
	over = 0;
	while (i < res->length)
	{
		tmp = res->block[i];
		res->block[i] = (tmp << 1) | over;
		over = tmp >> 31;
		++i;
	}
	if (over != 0)
	{
		res->block[i] = over;
		++res->length;
	}
}

void				bigint_mul10(t_bigint *res)
{
	uint64_t		over;
	uint64_t		mul;
	uint32_t		i;

	i = 0;
	over = 0;
	while (i < res->length)
	{
		mul = (uint64_t)(res->block[i]) * 10ull + over;
		(res->block[i]) = (uint32_t)(mul & 0xFFFFFFFF);
		over = mul >> 32;
		++i;
	}
	if (over != 0)
	{
		res->block[i] = (uint32_t)over;
		++res->length;
	}
}
