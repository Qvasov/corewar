/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x_xx_ll.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:38:28 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 15:38:30 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_x_ll(t_fstr *fstr, va_list *arg)
{
	char	x_ll[HEX_LL];
	char	sign[3];
	int		ord;
	int		w;
	char	base[17];

	ft_strcpy(base, "0123456789abcdef");
	fstr->uni.ullin = va_arg(*arg, unsigned long long int);
	ft_set_sign_x(fstr, sign);
	ord = ft_put_digit_hex_ll(x_ll, fstr->uni.ullin, HEX_LL, base);
	ord = (fstr->uni.ullin == 0 && fstr->prec == 0) ? 0 : ord;
	w = ft_max(fstr->prec, ord) + 2 * (sign[0] != 0);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
	{
		ft_check_ox(fstr, sign, 0);
		ft_print_int_width(fstr, sign + 2, fstr->wdth - w);
	}
	ft_check_ox(fstr, sign, 1);
	ft_print_int_prec(fstr, sign + 2, fstr->prec - ord);
	ft_buf_str(x_ll + HEX_LL - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, sign + 2, fstr->wdth - w);
}

void	ft_printf_xx_ll(t_fstr *fstr, va_list *arg)
{
	char	xx_ll[HEX_LL];
	char	sign[3];
	int		ord;
	int		w;
	char	base[17];

	ft_strcpy(base, "0123456789ABCDEF");
	fstr->uni.ullin = va_arg(*arg, unsigned long long int);
	ft_set_sign_xx(fstr, sign);
	ord = ft_put_digit_hex_ll(xx_ll, fstr->uni.ullin, HEX_LL, base);
	ord = (fstr->uni.ullin == 0 && fstr->prec == 0) ? 0 : ord;
	w = ft_max(fstr->prec, ord) + 2 * (sign[0] != 0);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
	{
		ft_check_ox(fstr, sign, 0);
		ft_print_int_width(fstr, sign + 2, fstr->wdth - w);
	}
	ft_check_ox(fstr, sign, 1);
	ft_print_int_prec(fstr, sign + 2, fstr->prec - ord);
	ft_buf_str(xx_ll + HEX_LL - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, sign + 2, fstr->wdth - w);
}
