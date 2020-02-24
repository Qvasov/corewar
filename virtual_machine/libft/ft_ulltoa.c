/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 16:42:03 by dbennie           #+#    #+#             */
/*   Updated: 2019/12/11 16:42:04 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(unsigned long long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char		*ft_ulltoa(unsigned long long n)
{
	char	*r;
	int		i;

	i = ft_count(n);
	if (!(r = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	r[i--] = '\0';
	if (n == 0)
		r[i] = 48;
	while (n)
	{
		r[i--] = n % 10 + 48;
		n = n / 10;
	}
	return (r);
}
