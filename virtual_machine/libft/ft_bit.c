/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 23:17:28 by ddarell           #+#    #+#             */
/*   Updated: 2019/12/22 23:17:30 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_bit_check(int flag, int position)
{
	return ((flag >> position) & 1);
}

void	ft_bit_on(int *flag, int position)
{
	*flag = *flag | (1 << position);
}

void	ft_bit_off(int *flag, int position)
{
	*flag = *flag & (~(1 << position));
}
