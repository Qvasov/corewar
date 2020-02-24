/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_bigint_pow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 02:25:02 by laleta            #+#    #+#             */
/*   Updated: 2019/06/21 02:36:48 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_dragon4.h"

void				bigint_pow2(t_bigint *res, uint32_t exp)
{
	uint32_t bit_idx;
	uint32_t block_idx;
	uint32_t i;

	i = 0;
	block_idx = exp / 32;
	while (i <= block_idx)
		res->block[i++] = 0;
	res->length = block_idx + 1;
	bit_idx = (exp % 32);
	res->block[block_idx] |= ((uint32_t)1 << bit_idx);
}

static inline void	bigint_mul10_bi(t_bigint **next, t_bigint **cur, uint32_t e)
{
	uint32_t	tab_idx;
	t_bigint	*swap;

	tab_idx = 0;
	e >>= 3;
	while (e != 0)
	{
		if (e & 1)
		{
			bigint_mul(*next, *cur, &g_pow_10_bi[tab_idx]);
			swap = *cur;
			*cur = *next;
			*next = swap;
		}
		++tab_idx;
		e >>= 1;
	}
}

void				bigint_pow10(t_bigint *res, uint32_t exp, t_bigint *tmp)
{
	t_bigint	*tmp_cur;
	t_bigint	*tmp_next;
	uint32_t	s_exp;

	tmp_cur = res;
	tmp_next = tmp;
	s_exp = exp & 0x7;
	bigint_set_32(tmp_cur, g_pow_10[s_exp]);
	bigint_mul10_bi(&tmp_next, &tmp_cur, exp);
	if (tmp_cur != res)
		bigint_cpy(res, tmp_cur);
}

void				bigint_mulpow10(t_bigint *res, uint32_t exp, t_bigint *tmp)
{
	t_bigint	*tmp_cur;
	t_bigint	*tmp_next;
	uint32_t	s_exp;

	s_exp = exp & 0x7;
	if (s_exp != 0)
	{
		bigint_mul_int(tmp, res, g_pow_10[s_exp]);
		tmp_cur = tmp;
		tmp_next = res;
	}
	else
	{
		tmp_cur = res;
		tmp_next = tmp;
	}
	bigint_mul10_bi(&tmp_next, &tmp_cur, exp);
	if (tmp_cur != res)
		bigint_cpy(res, tmp_cur);
}
