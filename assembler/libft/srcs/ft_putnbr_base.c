/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:06:19 by laleta            #+#    #+#             */
/*   Updated: 2019/04/07 20:44:43 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_base_err(const char *base)
{
	int			radix;
	int			i;
	int			j;

	i = 0;
	radix = ft_strlen(base);
	if (radix < 2)
		return (1);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-' || (base[i] < 32 || base[i] > 126))
			return (1);
		j = i + 1;
		while (base[j] && j < radix)
		{
			if (base[i] == base[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void		ft_putnbr_base(int nbr, const char *base)
{
	int			dec[10];
	int			i;
	long int	num;
	int			radix;

	if (ft_base_err(base))
		return ;
	radix = ft_strlen(base);
	num = nbr;
	i = 0;
	if (num < 0)
	{
		num *= -1;
		ft_putchar('-');
	}
	while (num >= radix)
	{
		dec[i++] = num % radix;
		num /= radix;
	}
	if (num < radix)
		dec[i] = num;
	while (i >= 0)
		ft_putchar(base[dec[i--]]);
}
