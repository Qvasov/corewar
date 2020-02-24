/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:37:02 by laleta            #+#    #+#             */
/*   Updated: 2020/02/24 15:59:57 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static short int	get_size(int n)
{
	short int		size;
	long int		nbr;

	nbr = n;
	size = 1;
	while ((nbr < 0 ? nbr * -1 : nbr) > 9)
	{
		nbr /= 10;
		size++;
	}
	if (nbr < 0)
		size++;
	return (size);
}

char				*ft_itoa(int n)
{
	long int		nbr;
	char			*num_arr;
	short int		size;

	size = get_size(n);
	if (!(num_arr = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	num_arr[size] = '\0';
	nbr = n;
	if (n < 0)
	{
		nbr *= -1;
		num_arr[0] = '-';
	}
	while (nbr > 9)
	{
		num_arr[--size] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (nbr <= 9)
		num_arr[--size] = nbr + '0';
	return (num_arr);
}
