/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 21:25:14 by ddarell           #+#    #+#             */
/*   Updated: 2019/05/08 21:46:42 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_int_tab(int *tab, size_t size)
{
	size_t	i;
	size_t	k;

	if (tab == NULL || size == 0 || size == 1)
		return ;
	k = 0;
	while (k < size)
	{
		i = 1;
		while (i < size)
		{
			if (tab[i - 1] > tab[i])
				ft_int_swap(tab + i - 1, tab + i);
			i++;
		}
		k++;
	}
	return ;
}
