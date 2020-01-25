/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_pow_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:58:54 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 15:59:32 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pow_to_array(char *buf, int ground, int pow)
{
	int					i;
	unsigned long long	base;

	i = 0;
	base = 1;
	while (i < pow)
	{
		while (i < pow && base < 0x1ffffffffffffff)
		{
			i++;
			base *= ground;
		}
		ft_rev_mult_array_num(buf, base);
		base = 1;
	}
}

int		ft_bin_pow_array(char *buf, int e)
{
	ft_strcpy(buf, "1");
	(e >= 0) ? ft_pow_to_array(buf, 2, e) : ft_pow_to_array(buf, 5, -e);
	return (e < 0 ? e + (int)ft_strlen(buf) - 1 : (int)ft_strlen(buf) - 1);
}
