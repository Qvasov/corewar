/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:06:26 by ddarell           #+#    #+#             */
/*   Updated: 2019/04/11 20:16:34 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	x;
	unsigned char	*y;
	size_t			i;

	x = (unsigned char)c;
	y = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		y[i] = x;
		i++;
	}
	return (b);
}
