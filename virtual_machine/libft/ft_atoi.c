/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:07:29 by ddarell           #+#    #+#             */
/*   Updated: 2019/05/09 19:50:39 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_space(char c)
{
	if (c == ' ' || c == '\r' || c == '\v' || c == '\f' || c == '\t'
		|| c == '\n')
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	size_t				i;
	int					sign;
	unsigned long int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (ft_check_space(str[i]) == 1)
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((res > 922337203685477580 || (res == 922337203685477580
		&& (str[i] - '0') > 7)) && sign == 1)
			return (-1);
		else if ((res > 922337203685477580 || (res == 922337203685477580
		&& (str[i] - '0') > 8)) && sign == -1)
			return (0);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(res * sign));
}
