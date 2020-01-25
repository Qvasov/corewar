/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_o_n_h_hh.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:47:48 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 15:48:10 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	check_sign(t_fstr *fstr, char *sign, int ord)
{
	if (ft_flag(fstr->flag, HASH))
	{
		if (fstr->uni.uin == 0)
		{
			if (fstr->prec != 0)
				*sign = 0;
			else
				*sign = '0';
		}
		else
		{
			*sign = '0';
			if (fstr->prec > ord)
				fstr->prec--;
		}
	}
	else
		*sign = 0;
}

void		ft_printf_o(t_fstr *fstr, va_list *arg)
{
	char	o[OCT];
	char	sign;
	int		ord;
	int		w;

	fstr->uni.uin = va_arg(*arg, unsigned int);
	ord = ft_put_digit_oct(o, fstr->uni.uin, OCT);
	ord = (fstr->uni.uin == 0 && fstr->prec == 0) ? 0 : ord;
	check_sign(fstr, &sign, ord);
	w = ft_max(fstr->prec, ord) + (sign != 0);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
	ft_print_int_prec(fstr, &sign, fstr->prec - ord);
	ft_buf_str(o + OCT - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
}

void		ft_printf_o_h(t_fstr *fstr, va_list *arg)
{
	char	o_h[OCT_H];
	char	sign;
	int		ord;
	int		w;

	fstr->uni.uin = (unsigned int)((unsigned short int)va_arg(*arg,
									unsigned int));
	ord = ft_put_digit_oct(o_h, fstr->uni.uin, OCT_H);
	ord = (fstr->uni.uin == 0 && fstr->prec == 0) ? 0 : ord;
	check_sign(fstr, &sign, ord);
	w = ft_max(fstr->prec, ord) + (sign != 0);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
	ft_print_int_prec(fstr, &sign, fstr->prec - ord);
	ft_buf_str(o_h + OCT_H - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
}

void		ft_printf_o_hh(t_fstr *fstr, va_list *arg)
{
	char	o_hh[OCT_HH];
	char	sign;
	int		ord;
	int		w;

	fstr->uni.uin = (unsigned int)((unsigned char)va_arg(*arg, unsigned int));
	ord = ft_put_digit_oct(o_hh, fstr->uni.uin, OCT_HH);
	ord = (fstr->uni.uin == 0 && fstr->prec == 0) ? 0 : ord;
	check_sign(fstr, &sign, ord);
	w = ft_max(fstr->prec, ord) + (sign != 0);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
	ft_print_int_prec(fstr, &sign, fstr->prec - ord);
	ft_buf_str(o_hh + OCT_HH - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
}
