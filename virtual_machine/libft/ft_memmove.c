/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 18:23:26 by ddarell           #+#    #+#             */
/*   Updated: 2019/04/23 21:38:35 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*a;
	unsigned char	*b;
	size_t			i;

	a = (unsigned char *)dst;
	b = (unsigned char *)src;
	i = 0;
	if (NULL == dst && NULL == src)
		return (0);
	if (a < b)
		while (i < len)
		{
			a[i] = b[i];
			i++;
		}
	else if (a > b)
		while (0 < len)
		{
			len--;
			a[len] = b[len];
		}
	return (dst);
}
