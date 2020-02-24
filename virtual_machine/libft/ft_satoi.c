/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_satoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 21:44:01 by ddarell           #+#    #+#             */
/*   Updated: 2020/01/12 13:38:38 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Special atoi function with error feedback.
**	If error occurred or no number found,
**	(*i) is set to 0 and returned value is 0. When no error, (*i) saves
**	number of chars atoi processed with
*/

static int	count_number(const char *str, int ord, int f, int *i)
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
		*i = 0;
	else if (nmb == 214748364)
	{
		if ((*str > '7' && f == 1) || (*str > '8' && f == -1))
			*i = 0;
		else
			return (f * (nmb * 10 + (*str - '0')));
	}
	else
		nmb = nmb * 10 + (*str - '0');
	if (!(*i))
		return (0);
	return (f * nmb);
}

int			ft_satoi(const char *str, int *i)
{
	int f;
	int ord;

	ord = 0;
	*i = 0;
	while (str[*i] == ' ' || str[*i] == '\r' || str[*i] == '\v'
	|| str[*i] == '\f' || str[*i] == '\t' || str[*i] == '\n')
		(*i)++;
	f = (str[*i] == '-') ? -1 : 1;
	if (str[*i] == '-' || str[*i] == '+')
		(*i)++;
	while (str[*i] == '0')
		(*i)++;
	while (*(str + ord + *i) >= '0' && *(str + ord + *i) <= '9')
		ord++;
	*i = (ord > 10 ||
		(ord == 0 && (*i == 0 || str[*i - 1] != '0'))) ? 0 : *i + ord;
	if (!(*i) || !(ord))
		return (0);
	return (count_number(str + *i - ord, ord, f, i));
}
