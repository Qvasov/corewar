/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoull.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 16:08:54 by dbennie           #+#    #+#             */
/*   Updated: 2019/12/11 16:08:55 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	ft_atoull(const char *str)
{
	unsigned long long	r;
	int					l;
	int					i;

	r = 0;
	l = 19;
	i = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v' ||\
			str[i] == '\r' || str[i] == '\f' || str[i] == ' ')
		++i;
	if (str[i] == '+')
	{
		++l;
		++i;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (i > l || ((i == l && r == 1844674407370955161) &&
						!(str[i] >= '0' && str[i] <= '5')))
			return (0);
		r = r * 10 + (str[i] - '0');
		++i;
	}
	return (r);
}
