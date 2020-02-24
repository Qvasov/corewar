/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matching_format.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:02:24 by ddarell           #+#    #+#             */
/*   Updated: 2019/12/02 19:30:33 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_match_flags(t_fstr *fstr, char *current)
{
	int i;

	i = 0;
	while (current[i] == '-' || current[i] == '+'
		|| current[i] == ' ' || current[i] == '0' || current[i] == '#')
	{
		if (current[i] == '-')
			fstr->flag |= (1 << MINUS);
		else if (current[i] == '+')
			fstr->flag |= (1 << PLUS);
		else if (current[i] == ' ')
			fstr->flag |= (1 << SPACE);
		else if (current[i] == '0')
			fstr->flag |= (1 << NOLL);
		else
			fstr->flag |= (1 << HASH);
		i++;
	}
	return (i);
}

int	ft_match_width(t_fstr *fstr, char *current, va_list *arg)
{
	int i;

	i = 0;
	if (*current <= '9' && *current >= '0')
	{
		fstr->wdth = ft_atoi((const char *)current);
		while (*current <= '9' && *current >= '0')
		{
			current++;
			i++;
		}
	}
	else if (*current == '*')
	{
		fstr->wdth = va_arg(*arg, int);
		if (fstr->wdth < 0)
		{
			fstr->wdth = ((unsigned)fstr->wdth == 0x80000000) ?
						0 : ~(fstr->wdth) + 1;
			fstr->flag |= (1 << MINUS);
		}
		i++;
	}
	return (i);
}

int	ft_match_prec(t_fstr *fstr, char *current, va_list *arg)
{
	int i;

	i = 1;
	if (*current != '.')
		return (0);
	current++;
	if (*current <= '9' && *current >= '0')
	{
		fstr->prec = ft_atoi((const char *)current);
		while (*current <= '9' && *current >= '0')
		{
			current++;
			i++;
		}
	}
	else if (*current == '*')
	{
		fstr->prec = va_arg(*arg, int);
		i++;
	}
	else
		fstr->prec = 0;
	return (i);
}
