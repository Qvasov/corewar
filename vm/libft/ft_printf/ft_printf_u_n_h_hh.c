/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u_n_h_hh.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:39:46 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 15:39:53 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_u(t_fstr *fstr, va_list *arg)
{
	char	u[DEC];
	char	sign;
	int		ord;
	int		w;

	fstr->uni.uin = va_arg(*arg, unsigned int);
	sign = 0;
	ord = ft_put_digit_dec(u, fstr->uni.uin, DEC);
	ord = (fstr->uni.uin == 0 && fstr->prec == 0) ? 0 : ord;
	w = ft_max(fstr->prec, ord);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
	ft_print_int_prec(fstr, &sign, fstr->prec - ord);
	ft_buf_str(u + DEC - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
}

void	ft_printf_u_h(t_fstr *fstr, va_list *arg)
{
	char	u_h[DEC_H];
	char	sign;
	int		ord;
	int		w;

	fstr->uni.uin = (unsigned int)((unsigned short int)va_arg(*arg,
									unsigned int));
	sign = 0;
	ord = ft_put_digit_dec(u_h, fstr->uni.uin, DEC_H);
	ord = (fstr->uni.uin == 0 && fstr->prec == 0) ? 0 : ord;
	w = ft_max(fstr->prec, ord);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
	ft_print_int_prec(fstr, &sign, fstr->prec - ord);
	ft_buf_str(u_h + DEC_H - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
}

void	ft_printf_u_hh(t_fstr *fstr, va_list *arg)
{
	char	u_hh[DEC_HH];
	char	sign;
	int		ord;
	int		w;

	fstr->uni.uin = (unsigned int)((unsigned char)va_arg(*arg, unsigned int));
	sign = 0;
	ord = ft_put_digit_dec(u_hh, fstr->uni.uin, DEC_HH);
	ord = (fstr->uni.uin == 0 && fstr->prec == 0) ? 0 : ord;
	w = ft_max(fstr->prec, ord);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
	ft_print_int_prec(fstr, &sign, fstr->prec - ord);
	ft_buf_str(u_hh + DEC_HH - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
}
