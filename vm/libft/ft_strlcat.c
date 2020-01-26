/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 18:20:14 by ddarell           #+#    #+#             */
/*   Updated: 2019/04/25 20:40:47 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	i = len_dst;
	if (size < len_dst)
		return (len_src + size);
	while (*src && i + 1 < size)
	{
		dst[i] = *src;
		i++;
		src++;
	}
	dst[i] = 0;
	return (len_dst + len_src);
}
