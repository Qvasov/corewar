/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_int_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 23:17:15 by ddarell           #+#    #+#             */
/*   Updated: 2019/12/22 23:17:16 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_search_int_tab(int *tab, int size, int num)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (tab[i] == num)
			return (i);
		i++;
	}
	return (-1);
}
