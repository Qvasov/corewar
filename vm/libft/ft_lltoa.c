/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:51:23 by dbennie           #+#    #+#             */
/*   Updated: 2019/11/06 13:51:25 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(long long n)
{
	int	i;

	i = 0;
	if ((unsigned long long)n == 0x8000000000000000)
		return (20);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char		*ft_lltoa(long long n)
{
	char	*r;
	int		i;

	i = ft_count(n);
	if (!(r = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	r[i--] = '\0';
	if (n == 0)
		r[i] = 48;
	if ((unsigned long long)n == 0x8000000000000000)
	{
		r[i--] = '8';
		n = n / 10;
	}
	if (n < 0)
	{
		r[0] = '-';
		n *= -1;
	}
	while (n)
	{
		r[i--] = n % 10 + 48;
		n = n / 10;
	}
	return (r);
}
