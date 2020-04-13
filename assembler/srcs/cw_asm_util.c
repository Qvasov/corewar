/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_asm_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 20:11:18 by laleta            #+#    #+#             */
/*   Updated: 2020/02/24 12:54:51 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_asm.h"
#include "cw_asm_hash.h"

int8_t		is_insignificant(int32_t c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == SEPARATOR_CHAR);
}

uint8_t		get_bits(uint8_t i, uint8_t arg_code)
{
	uint8_t shift;

	shift = 6 - 2 * i;
	return ((arg_code & (3 << shift)) >> shift);
}

uint16_t	swap_byte2(uint16_t nbr)
{
	uint8_t res[2];

	*((uint16_t *)res) = nbr;
	return (((uint16_t)res[1]) | ((uint16_t)res[0] << 8));
}

uint32_t	swap_byte4(uint32_t nbr)
{
	uint8_t res[4];

	*((uint32_t *)res) = nbr;
	return (((uint32_t)res[3]) | ((uint32_t)res[2] << 8)
						| ((uint32_t)res[1] << 16) | ((uint32_t)res[0] << 24));
}

uint64_t	get_hash(const char *str)
{
	uint64_t	hash;
	uint32_t	i;

	i = 0;
	hash = 0;
	while (str[i])
	{
		hash += (str[i] - 'a' + 1) * g_hash_pow[i % 1024];
		i++;
	}
	return (hash);
}
