/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xx_n_h_hh.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:36:42 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 15:37:25 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_xx(t_fstr *fstr, va_list *arg)
{
	char	xx[HEX];
	char	sign[3];
	int		ord;
	int		w;
	char	base[17];

	ft_strcpy(base, "0123456789ABCDEF");
	fstr->uni.uin = va_arg(*arg, unsigned int);
	ft_set_sign_xx(fstr, sign);
	ord = ft_put_digit_hex(xx, fstr->uni.uin, HEX, base);
	ord = (fstr->uni.uin == 0 && fstr->prec == 0) ? 0 : ord;
	w = ft_max(fstr->prec, ord) + 2 * (sign[0] != 0);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
	{
		ft_check_ox(fstr, sign, 0);
		ft_print_int_width(fstr, sign + 2, fstr->wdth - w);
	}
	ft_check_ox(fstr, sign, 1);
	ft_print_int_prec(fstr, sign + 2, fstr->prec - ord);
	ft_buf_str(xx + HEX - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, sign + 2, fstr->wdth - w);
}

void	ft_printf_xx_h(t_fstr *fstr, va_list *arg)
{
	char	x_h[HEX_H];
	char	sign[3];
	int		ord;
	int		w;
	char	base[17];

	ft_strcpy(base, "0123456789ABCDEF");
	fstr->uni.uin = (unsigned int)((unsigned short int)va_arg(*arg,
									unsigned int));
	ft_set_sign_xx(fstr, sign);
	ord = ft_put_digit_hex(x_h, fstr->uni.uin, HEX_H, base);
	ord = (fstr->uni.uin == 0 && fstr->prec == 0) ? 0 : ord;
	w = ft_max(fstr->prec, ord) + 2 * (sign[0] != 0);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
	{
		ft_check_ox(fstr, sign, 0);
		ft_print_int_width(fstr, sign + 2, fstr->wdth - w);
	}
	ft_check_ox(fstr, sign, 1);
	ft_print_int_prec(fstr, sign + 2, fstr->prec - ord);
	ft_buf_str(x_h + HEX_H - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, sign + 2, fstr->wdth - w);
}

void	ft_printf_xx_hh(t_fstr *fstr, va_list *arg)
{
	char	x_hh[HEX_HH];
	char	sign[3];
	int		ord;
	int		w;
	char	base[17];

	ft_strcpy(base, "0123456789ABCDEF");
	fstr->uni.uin = (unsigned int)((unsigned char)va_arg(*arg, unsigned int));
	ft_set_sign_xx(fstr, sign);
	ord = ft_put_digit_hex(x_hh, fstr->uni.uin, HEX_HH, base);
	ord = (fstr->uni.uin == 0 && fstr->prec == 0) ? 0 : ord;
	w = ft_max(fstr->prec, ord) + 2 * (sign[0] != 0);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
	{
		ft_check_ox(fstr, sign, 0);
		ft_print_int_width(fstr, sign + 2, fstr->wdth - w);
	}
	ft_check_ox(fstr, sign, 1);
	ft_print_int_prec(fstr, sign + 2, fstr->prec - ord);
	ft_buf_str(x_hh + HEX_HH - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, sign + 2, fstr->wdth - w);
}
