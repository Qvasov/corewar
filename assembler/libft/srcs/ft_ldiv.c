/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldiv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 04:16:09 by laleta            #+#    #+#             */
/*   Updated: 2019/06/21 04:16:40 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ldiv_t	ft_ldiv(long num, long denom)
{
	t_ldiv_t res;

	res.quot = num / denom;
	res.rem = num - denom * res.quot;
	if (res.quot < 0 && res.rem > 0)
	{
		res.quot += 1;
		res.rem -= denom;
	}
	return (res);
}
