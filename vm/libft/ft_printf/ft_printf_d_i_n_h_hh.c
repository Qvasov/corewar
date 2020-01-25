/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d_i_n_h_hh.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:56:29 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 15:56:30 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	check_sign(t_fstr *fstr, char *sign)
{
	if (fstr->uni.in < 0)
	{
		*sign = '-';
		fstr->uni.uin = (unsigned int)(~(fstr->uni.in) + 1);
	}
	else
	{
		fstr->uni.uin = (unsigned int)fstr->uni.in;
		if (ft_flag(fstr->flag, PLUS))
			*sign = '+';
		else if (ft_flag(fstr->flag, SPACE))
			*sign = ' ';
		else
			*sign = 0;
	}
}

void		ft_printf_d_i(t_fstr *fstr, va_list *arg)
{
	char	d_i[DEC];
	char	sign;
	int		ord;
	int		w;

	fstr->uni.in = va_arg(*arg, int);
	check_sign(fstr, &sign);
	ord = ft_put_digit_dec(d_i, fstr->uni.uin, DEC);
	ord = (fstr->uni.uin == 0 && fstr->prec == 0) ? 0 : ord;
	w = ft_max(fstr->prec, ord) + (sign != 0);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
	ft_print_int_prec(fstr, &sign, fstr->prec - ord);
	ft_buf_str(d_i + DEC - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
}

void		ft_printf_d_i_h(t_fstr *fstr, va_list *arg)
{
	char	d_i_h[DEC_H];
	char	sign;
	int		ord;
	int		w;

	fstr->uni.in = (int)((short int)va_arg(*arg, int));
	check_sign(fstr, &sign);
	ord = ft_put_digit_dec(d_i_h, fstr->uni.uin, DEC_H);
	ord = (fstr->uni.uin == 0 && fstr->prec == 0) ? 0 : ord;
	w = ft_max(fstr->prec, ord) + (sign != 0);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
	ft_print_int_prec(fstr, &sign, fstr->prec - ord);
	ft_buf_str(d_i_h + DEC_H - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
}

void		ft_printf_d_i_hh(t_fstr *fstr, va_list *arg)
{
	char	d_i_hh[DEC_HH];
	char	sign;
	int		ord;
	int		w;

	fstr->uni.in = (int)((char)va_arg(*arg, int));
	check_sign(fstr, &sign);
	ord = ft_put_digit_dec(d_i_hh, fstr->uni.uin, DEC_HH);
	ord = (fstr->uni.uin == 0 && fstr->prec == 0) ? 0 : ord;
	w = ft_max(fstr->prec, ord) + (sign != 0);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
	ft_print_int_prec(fstr, &sign, fstr->prec - ord);
	ft_buf_str(d_i_hh + DEC_HH - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
}
