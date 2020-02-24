/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 17:53:52 by laleta            #+#    #+#             */
/*   Updated: 2019/04/08 03:38:17 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = -1;
	if (src < dst)
		while ((int)(--len) >= 0)
		{
			((unsigned char*)dst)[len] = ((unsigned char*)src)[len];
		}
	else
		while (++i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		}
	return (dst);
}
