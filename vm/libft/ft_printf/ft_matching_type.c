/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matching_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:59:40 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 16:00:46 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	flg(int f)
{
	int i;

	i = 1;
	while (i < IFG_NUM)
	{
		if (f & 1)
			break ;
		f = f >> 1;
		i++;
	}
	return (i < IFG_NUM ? i : 0);
}

static void	match_after_i(t_fstr *fstr, char current)
{
	if (current == 's')
		fstr->flag |= (2 << TYPE);
	else if (current == 'u')
		fstr->flag |= ((4 + IFG_NUM * 2
						+ flg(fstr->flag >> LONG_LONG)) << TYPE);
	else if (current == 'p')
		fstr->flag |= (3 << TYPE);
	else if (current == 'x')
		fstr->flag |= ((4 + IFG_NUM * 4
						+ flg(fstr->flag >> LONG_LONG)) << TYPE);
	else if (current == 'o')
		fstr->flag |= ((4 + IFG_NUM + flg(fstr->flag >> LONG_LONG)) << TYPE);
}

static void	match_before_i(t_fstr *fstr, char current)
{
	if (current == 'f')
		fstr->flag |= ((4 + IFG_NUM * 5
						+ (ft_flag(fstr->flag, LONG_DOUBLE) > 0)) << TYPE);
	else if (current == 'c')
		fstr->flag |= (1 << TYPE);
	else if (current == 'X')
		fstr->flag |= ((4 + IFG_NUM * 3
						+ flg(fstr->flag >> LONG_LONG)) << TYPE);
	else if (current == '%')
		fstr->flag |= (31 << TYPE);
	else if (current == 'b')
		fstr->flag |= ((32 + flg(fstr->flag >> LONG_LONG)) << TYPE);
	else if (current == 'e')
		fstr->flag |= ((37 + (ft_flag(fstr->flag, LONG_DOUBLE) > 0)) << TYPE);
	else if (current == 'E')
		fstr->flag |= ((39 + (ft_flag(fstr->flag, LONG_DOUBLE) > 0)) << TYPE);
}

int			ft_match_type(t_fstr *fstr, char *current)
{
	if (*current == 'd' || *current == 'i')
		fstr->flag |= ((4 + flg(fstr->flag >> LONG_LONG)) << TYPE);
	else if (*current < 'i')
		match_before_i(fstr, *current);
	else if (*current > 'i')
		match_after_i(fstr, *current);
	if ((fstr->flag >> TYPE) > 0)
		fstr->strl += 1;
	return (0);
}
