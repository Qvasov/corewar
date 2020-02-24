/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_dragon4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 02:18:36 by laleta            #+#    #+#             */
/*   Updated: 2019/06/30 23:35:54 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_dragon4.h"

static void		dragon4_get_exp10(t_bigint **bigints, const uint32_t mantis_bit,
										const int32_t exp_in, int32_t *exp_10)
{
	t_bigint	*tmp1;
	t_bigint	*tmp2;
	t_bigint	*tmp;
	t_bigint	*pow10;

	tmp1 = &(*bigints)[3];
	tmp2 = &(*bigints)[4];
	*exp_10 = (int32_t)(ft_ceil((double)((int32_t)mantis_bit + exp_in) * LOG10_2
																	- 0.69));
	if (*exp_10 > 0)
		bigint_mulpow10(&(*bigints)[1], *exp_10, tmp1);
	else if (*exp_10 < 0)
	{
		tmp = tmp1;
		pow10 = tmp2;
		bigint_pow10(pow10, -*exp_10, tmp);
		bigint_mul(tmp, &(*bigints)[2], pow10);
		bigint_cpy(&(*bigints)[2], tmp);
	}
	if (bigint_cmp(&(*bigints)[2], &(*bigints)[1]) >= 0)
		++*exp_10;
	else
		bigint_mul10(&(*bigints)[2]);
}

static uint32_t	dragon4_get_digit(char **buf, int32_t exp_10, t_bigint **scale,
														t_bigint **scaled_val)
{
	int32_t		hi_block;
	uint32_t	shift;
	int32_t		exp_cut;
	uint32_t	digit;

	exp_cut = exp_10 - (DR_BUFSIZE - 1);
	hi_block = (*scale)->block[(*scale)->length - 1];
	if (hi_block < 8 || hi_block > 429496729)
	{
		shift = (32 + 27 - log_2_32(hi_block)) % 32;
		bigint_shiftl(*scale, shift);
		bigint_shiftl(*scaled_val, shift);
	}
	while (1)
	{
		exp_10 = exp_10 - 1;
		digit = bigint_div(*scaled_val, *scale);
		if (((*scaled_val)->length == 0) | (exp_10 == exp_cut))
			break ;
		**buf = (char)(digit + '0');
		++*buf;
		bigint_mul10(*scaled_val);
	}
	return (digit);
}

static int32_t	dragon4_round_up(char **buf_cur, char *buf)
{
	int32_t		exp_inc;

	exp_inc = 0;
	while (1)
	{
		if (*buf_cur == buf)
		{
			**buf_cur = '1';
			++*buf_cur;
			++exp_inc;
			break ;
		}
		--*buf_cur;
		if (**buf_cur != '9')
		{
			**buf_cur += 1;
			++*buf_cur;
			break ;
		}
	}
	return (exp_inc);
}

static int32_t	dragon4_round(char **buf_cur, char *buf, uint32_t digit,
															t_bigint **bigints)
{
	int32_t		cmp;
	int32_t		round_down;
	int32_t		exp_inc;

	exp_inc = 0;
	bigint_mul2(&(*bigints)[2]);
	cmp = bigint_cmp(&(*bigints)[2], &(*bigints)[1]);
	round_down = ((cmp < 0) || (cmp == 0 && !(digit & 1))) ? 1 : 0;
	if (round_down)
	{
		**buf_cur = (char)('0' + digit);
		++*buf_cur;
	}
	else
	{
		if (digit == 9)
			exp_inc = dragon4_round_up(buf_cur, buf);
		else
		{
			**buf_cur = (char)('0' + digit + 1);
			++*buf_cur;
		}
	}
	return (exp_inc);
}

uint32_t		dragon4_solve(t_bigint *bigints, t_float80 *num, char *buf,
															int32_t *exp_out)
{
	t_bigint	*scale;
	t_bigint	*scaled_val;
	char		*buf_cur;
	int32_t		exp_10;
	uint32_t	dig_out;

	buf_cur = buf;
	scale = &bigints[1];
	scaled_val = &bigints[2];
	bigint_cpy(scaled_val, &bigints[0]);
	if (num->exponent > 0)
	{
		bigint_shiftl(scaled_val, num->exponent + 1);
		bigint_set_32(scale, 2);
	}
	else
	{
		bigint_shiftl(scaled_val, 1);
		bigint_pow2(scale, -num->exponent + 1);
	}
	dragon4_get_exp10(&bigints, num->mantis_bit, num->exponent, &exp_10);
	*exp_out = exp_10 - 1;
	dig_out = dragon4_get_digit(&buf_cur, exp_10, &scale, &scaled_val);
	*exp_out += dragon4_round(&buf_cur, buf, dig_out, &bigints);
	return ((uint32_t)(buf_cur - buf));
}
