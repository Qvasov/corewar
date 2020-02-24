/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_scale.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 02:28:32 by laleta            #+#    #+#             */
/*   Updated: 2019/06/30 20:41:24 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int16_t			ft_get_inf_nan(long double *num)
{
	uint16_t	*n;
	int16_t		e;

	n = (uint16_t *)num;
	e = n[4] & 0x7fff;
	if (e == 0x7fff)
		return (n[3] & 0x7fff || n[2] || n[1] || n[0] ? NAN : INF);
	else if (n[3] == 0 && n[2] == 0 && n[1] == 0 && n[0] == 0)
		return (0);
	else
		return (-1);
}

void			ft_get_exp_mant(long double *num, int32_t *exp, uint64_t *mant)
{
	const uint64_t	*num_i = (uint64_t *)num;

	if ((num_i[1] & 0x7FFF) != 0)
	{
		*mant = (num_i[0] & 0x7FFFFFFFFFFFFFFF);
		*mant <<= 1;
		*exp = (num_i[1] & 0x7FFF) - 16383;
	}
	else
	{
		*exp = 1 - 16383;
		*mant = num_i[0] & 0x7FFFFFFFFFFFFFFF;
	}
}
