/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_b_n_h_hh.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 21:08:57 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/29 21:08:58 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_b(t_fstr *fstr, va_list *arg)
{
	char	b[BIN];
	char	sign;
	int		ord;
	int		w;

	fstr->uni.uin = va_arg(*arg, unsigned int);
	ord = ft_put_digit_bin(b, fstr->uni.uin, BIN);
	ord = (fstr->uni.uin == 0 && fstr->prec == 0) ? 0 : ord;
	sign = 0;
	w = ft_max(fstr->prec, ord);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
	ft_print_int_prec(fstr, &sign, fstr->prec - ord);
	ft_buf_str(b + BIN - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
}

void		ft_printf_b_h(t_fstr *fstr, va_list *arg)
{
	char	b_h[BIN_H];
	char	sign;
	int		ord;
	int		w;

	fstr->uni.uin = (unsigned int)((unsigned short int)va_arg(*arg,
	unsigned int));
	ord = ft_put_digit_bin(b_h, fstr->uni.uin, BIN_H);
	ord = (fstr->uni.uin == 0 && fstr->prec == 0) ? 0 : ord;
	sign = 0;
	w = ft_max(fstr->prec, ord);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
	ft_print_int_prec(fstr, &sign, fstr->prec - ord);
	ft_buf_str(b_h + BIN_H - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
}

void		ft_printf_b_hh(t_fstr *fstr, va_list *arg)
{
	char	b_hh[BIN_HH];
	char	sign;
	int		ord;
	int		w;

	fstr->uni.uin = (unsigned int)((unsigned char)va_arg(*arg, unsigned int));
	ord = ft_put_digit_bin(b_hh, fstr->uni.uin, BIN_HH);
	ord = (fstr->uni.uin == 0 && fstr->prec == 0) ? 0 : ord;
	sign = 0;
	w = ft_max(fstr->prec, ord);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
	ft_print_int_prec(fstr, &sign, fstr->prec - ord);
	ft_buf_str(b_hh + BIN_HH - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
}
