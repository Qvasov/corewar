/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 20:34:45 by dbennie           #+#    #+#             */
/*   Updated: 2019/10/07 17:14:17 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(const char *str)
{
	unsigned long long	r;
	int					i;
	long long			s;

	i = 0;
	s = 1;
	r = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v' ||\
			str[i] == '\r' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		s = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		if (r >= 9223372036854775807 && s == 1)
			return (-1);
		else if (r > 9223372036854775807 && s == -1)
			return (0);
		i++;
	}
	return ((long long)r * s);
}
