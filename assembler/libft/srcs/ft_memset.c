/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:02:05 by laleta            #+#    #+#             */
/*   Updated: 2019/04/08 02:07:26 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memset(void *b, int c, size_t len)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = (char *)b;
	while (i < len)
		dest[i++] = (unsigned char)c;
	return (b);
}
