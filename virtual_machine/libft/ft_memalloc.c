/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 21:15:21 by ddarell           #+#    #+#             */
/*   Updated: 2019/05/02 20:06:40 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *ptr;

	if (size == 0)
		return (NULL);
	if ((ptr = malloc(1 * size)) == NULL)
		return (NULL);
	ft_bzero(ptr, size);
	return (ptr);
}
