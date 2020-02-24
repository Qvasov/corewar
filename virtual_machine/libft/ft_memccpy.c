/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 22:57:00 by ddarell           #+#    #+#             */
/*   Updated: 2019/04/12 18:03:48 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;
	unsigned int	s;
	size_t			i;

	a = (unsigned char *)dst;
	b = (unsigned char *)src;
	s = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		a[i] = b[i];
		i++;
		if (b[i - 1] == s)
			return (a + i);
	}
	return (NULL);
}
