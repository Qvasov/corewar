/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_spec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 21:44:01 by ddarell           #+#    #+#             */
/*   Updated: 2019/12/08 21:44:24 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_number(const char *str, int ord, int f)
{
	int			nmb;
	const char	*end;

	nmb = 0;
	end = str + ord - 1;
	while (str < end)
	{
		nmb *= 10;
		nmb += (*str - '0');
		str++;
	}
	if (nmb > 214748364)
		return (0);
	else if (nmb == 214748364)
	{
		if ((*str > '7' && f == 1) || (*str > '8' && f == -1))
			return (0);
		return (f * nmb * 10 + f * (*str - '0'));
	}
	else
		nmb = nmb * 10 + (*str - '0');
	return (f * nmb);
}

int			ft_atoi_spec(const char *str)
{
	int f;
	int ord;

	ord = 0;
	while (*str == ' ' || *str == '\r' || *str == '\v'
			|| *str == '\f' || *str == '\t' || *str == '\n')
		str++;
	f = (*str == '-') ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	while (*(str + ord) >= '0' && *(str + ord) <= '9')
		ord++;
	if (ord > 10 || ord == 0)
		return (0);
	return (count_number(str, ord, f));
}
