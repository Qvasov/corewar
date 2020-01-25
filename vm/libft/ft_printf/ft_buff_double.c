/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buff_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:04:11 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 16:04:46 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_buff_double_width(t_fstr *fstr, char *sign, int len)
{
	char symb;

	symb = (ft_flag(fstr->flag, MINUS)
			|| !(ft_flag(fstr->flag, NOLL))) ? ' ' : '0';
	if (symb == '0' && *sign)
	{
		ft_buf_smb(*sign, 1, fstr);
		*sign = 0;
	}
	if (len > 0)
		ft_buf_smb(symb, len, fstr);
	fstr->wdth = 0;
}

static int	buff_after_point(char *res, t_dbl *dbl, t_fstr *fstr)
{
	int len;

	len = (fstr->prec < dbl->len) ? fstr->prec : dbl->len;
	ft_buf_str(res, len, fstr);
	fstr->prec -= len;
	return (0);
}

static int	buff_before_point(char *res, t_dbl *dbl, t_fstr *fstr)
{
	if (dbl->sign)
	{
		ft_buf_smb(dbl->sign, 1, fstr);
		dbl->sign = 0;
	}
	if (dbl->ord >= 0)
		ft_buf_str(res, dbl->ord + 1, fstr);
	else
		ft_buf_smb('0', 1, fstr);
	if (dbl->point)
		ft_buf_smb(dbl->point, 1, fstr);
	return (dbl->ord >= 0 ? dbl->ord + 1 : 0);
}

void		ft_buff_double(t_fstr *fstr, char *res, t_dbl *dbl)
{
	int nulls;
	int tmp;

	tmp = buff_before_point(res, dbl, fstr);
	res += tmp;
	dbl->len -= tmp;
	if (dbl->ord < 0)
	{
		nulls = (fstr->prec > -(dbl->ord) - 1) ? -(dbl->ord) - 1 : fstr->prec;
		ft_buf_smb('0', nulls, fstr);
		fstr->prec -= nulls;
	}
	buff_after_point(res, dbl, fstr);
	if (fstr->prec > 0)
		ft_buf_smb('0', fstr->prec, fstr);
}
