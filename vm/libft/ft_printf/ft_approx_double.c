/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_approx_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:04:53 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/29 21:06:44 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_five(char *res, int depth)
{
	int i;

	i = 1;
	if (depth - 1 >= 0 && res[depth - 1] % 2 == 1)
		return (1);
	else
		while (res[depth + i] == '0' && i < 25)
			i++;
	return (((i == 25 || res[depth + i] == 0) ? 0 : 1));
}

static int	check_round(char *res, t_dbl *dbl, int depth)
{
	int round_flag;

	dbl->len = ft_strlen(res);
	round_flag = 0;
	if (depth >= 0 && depth < dbl->len)
	{
		round_flag = (res[depth] > '5') ? 1 : 0;
		if (res[depth] == '5')
		{
			round_flag = check_five(res, depth);
		}
		res[depth] = 0;
		dbl->len = depth;
	}
	return (round_flag);
}

void		ft_approx_double(char *res, t_dbl *dbl, int prec)
{
	int depth;

	depth = prec + dbl->ord + 1;
	if (!(check_round(res, dbl, depth)))
		return ;
	while (--depth >= 0)
	{
		if (res[depth] == '9')
			res[depth] = '0';
		else
		{
			res[depth] += 1;
			break ;
		}
	}
	if (depth < 0)
	{
		dbl->res[0] = '1';
		dbl->ord += 1;
		dbl->len += 1;
	}
}
