/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:15:09 by ddarell           #+#    #+#             */
/*   Updated: 2019/04/12 20:25:45 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*a;
	unsigned int	sign;
	size_t			i;

	a = (unsigned char *)s;
	sign = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (a[i] == sign)
			return (a + i);
		i++;
	}
	return (NULL);
}
