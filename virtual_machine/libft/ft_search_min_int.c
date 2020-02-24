/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_min_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 23:16:50 by ddarell           #+#    #+#             */
/*   Updated: 2019/12/22 23:16:57 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_seach_min_int(int *tab, int size)
{
	int min;

	min = *tab;
	while (--size)
	{
		tab++;
		if (*tab < min)
			min = *tab;
	}
	return (min);
}
