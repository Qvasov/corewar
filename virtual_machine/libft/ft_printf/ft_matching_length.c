/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matching_length.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:01:04 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/29 21:07:06 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	match_hh(t_fstr *fstr, char *current, int *i)
{
	if (*current == 'h')
	{
		fstr->flag |= (1 << SHORT_SHORT);
		*i += 1;
	}
	else
		fstr->flag |= (1 << SHORT);
}

static void	match_ll(t_fstr *fstr, char *current, int *i)
{
	if (*current == 'l')
	{
		fstr->flag |= (1 << LONG_LONG);
		*i += 1;
	}
	else
		fstr->flag |= (1 << LONG);
}

int			ft_match_length(t_fstr *fstr, char *current)
{
	int i;

	i = 0;
	while (current[i] == 'l' || current[i] == 'h' || current[i] == 'L')
	{
		if (current[i] == 'l')
			match_ll(fstr, current + 1, &i);
		else if (current[i] == 'h')
			match_hh(fstr, current + 1, &i);
		else if (current[i] == 'L')
			fstr->flag |= (1 << LONG_DOUBLE);
		i++;
	}
	return (i);
}
