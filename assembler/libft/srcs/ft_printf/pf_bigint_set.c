/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_bigint_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 02:26:47 by laleta            #+#    #+#             */
/*   Updated: 2019/06/21 03:49:00 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pf_dragon4.h"

uint32_t	log_2_32(uint32_t val)
{
	uint32_t	tmp;

	tmp = val >> 24;
	if (tmp)
		return (24 + g_log_2[tmp]);
	tmp = val >> 16;
	if (tmp)
		return (16 + g_log_2[tmp]);
	tmp = val >> 8;
	if (tmp)
		return (8 + g_log_2[tmp]);
	return (g_log_2[val]);
}

uint32_t	log_2_64(uint64_t val)
{
	uint64_t	tmp;

	tmp = val >> 32;
	if (tmp)
		return (32 + log_2_32((uint32_t)tmp));
	return (log_2_32((uint32_t)val));
}

void		bigint_set_64(t_bigint *bi, uint64_t value)
{
	if (value > 0xFFFFFFFF)
	{
		bi->block[0] = value & 0xFFFFFFFF;
		bi->block[1] = (value >> 32) & 0xFFFFFFFF;
		bi->length = 2;
	}
	else if (value != 0)
	{
		bi->block[0] = value & 0xFFFFFFFF;
		bi->length = 1;
	}
	else
		bi->length = 0;
}

void		bigint_set_32(t_bigint *bi, uint32_t value)
{
	if (value != 0)
	{
		bi->block[0] = value;
		bi->length = 1;
	}
	else
		bi->length = 0;
}

uint32_t	dragon4(char *buffer, t_bigint *bigints, long double *num,
															int32_t *exp_out)
{
	t_float80		num_f;
	int32_t			dig_cnt;
	int32_t			count;
	const uint64_t	*num_i = (uint64_t *)num;

	if ((num_i[1] & 0x7FFF) != 0)
	{
		num_f.mantissa = (1ull << 63) | (num_i[0] & 0x7FFFFFFFFFFFFFFF);
		num_f.exponent = (num_i[1] & 0x7FFF) - 16383 - 63;
		num_f.mantis_bit = 63;
	}
	else
	{
		num_f.mantissa = num_i[0] & 0x7FFFFFFFFFFFFFFF;
		num_f.exponent = 1 - 16383 - 63;
		num_f.mantis_bit = log_2_64(num_f.mantissa);
	}
	bigint_set_64(&bigints[0], num_f.mantissa);
	dig_cnt = dragon4_solve(bigints, &num_f, buffer, exp_out);
	count = *exp_out + 1 - dig_cnt;
	if (count > 0 && count + dig_cnt < (DR_BUFSIZE - 1))
		while (count-- > 0)
			buffer[dig_cnt++] = '0';
	buffer[dig_cnt] = '\0';
	return (dig_cnt);
}
