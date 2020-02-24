/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:34:12 by laleta            #+#    #+#             */
/*   Updated: 2019/04/11 00:31:53 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_nbr_base(long int nbr, const char *base, int size)
{
	char		*nb_str;
	int			radix;

	nb_str = malloc(sizeof(char) * size + 2);
	radix = ft_strlen(base);
	if (nbr < 0)
	{
		nbr *= -1;
		size++;
		nb_str[0] = '-';
	}
	nb_str[size + 1] = '\0';
	while (nbr >= radix)
	{
		nb_str[size--] = base[nbr % radix];
		nbr /= radix;
	}
	if (nbr < radix)
		nb_str[size] = base[nbr];
	return (nb_str);
}

char			*ft_convert_base(const char *nbr, const char *base_from,
								const char *base_to)
{
	long int	nbr_dec;
	long int	n;
	int			radix_to;
	int			size;

	size = 0;
	radix_to = ft_strlen(base_to);
	nbr_dec = ft_atoi_base(nbr, base_from);
	n = nbr_dec;
	while (n >= radix_to)
	{
		size++;
		n /= radix_to;
	}
	return (ft_nbr_base(nbr_dec, base_to, size));
}
