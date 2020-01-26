/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 21:05:26 by ddarell           #+#    #+#             */
/*   Updated: 2019/04/12 21:11:20 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				d;
	unsigned char	*a;
	unsigned char	*b;
	size_t			i;

	d = 0;
	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if ((d = a[i] - b[i]) != 0)
			return (d);
		i++;
	}
	return (d);
}
