/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:40:10 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 15:40:32 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_l(int a, size_t b)
{
	if (a < 0)
		return (b);
	if (a > (int)b)
		return ((int)b);
	return (a);
}

void		ft_print_str_width(t_fstr *fstr, int l)
{
	char c;

	c = (ft_flag(fstr->flag, MINUS) || !(ft_flag(fstr->flag, NOLL)))
		? ' ' : '0';
	ft_buf_smb(c, fstr->wdth - l, fstr);
	fstr->wdth = l;
}

void		ft_printf_string(t_fstr *fstr, va_list *arg)
{
	char	*s;
	int		l;

	if ((s = va_arg(*arg, char *)) == NULL)
		s = "(null)";
	l = check_l(fstr->prec, ft_strlen(s));
	if (fstr->wdth > l && !(ft_flag(fstr->flag, MINUS)))
		ft_print_str_width(fstr, l);
	ft_buf_str(s, l, fstr);
	if (fstr->wdth > l)
		ft_print_str_width(fstr, l);
}
