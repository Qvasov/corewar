/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 21:58:06 by ddarell           #+#    #+#             */
/*   Updated: 2019/04/11 22:05:06 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*y;
	size_t			i;

	y = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		y[i] = 0;
		i++;
	}
	return ;
}
