/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:40:46 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 15:51:27 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_pointer(t_fstr *fstr, va_list *arg)
{
	char	x[HEX_LL];
	char	sign[3];
	int		ord;
	int		w;
	char	base[17];

	ft_strcpy(base, "0123456789abcdef");
	fstr->uni.ullin = (unsigned long long)(va_arg(*arg, void *));
	ft_strcpy(sign, "0x");
	ord = ft_put_digit_hex_ll(x, fstr->uni.ullin, HEX_LL, base);
	ord = (fstr->uni.ullin == 0 && fstr->prec == 0) ? 0 : ord;
	w = ft_max(fstr->prec, ord) + 2;
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
	{
		ft_check_ox(fstr, sign, 0);
		ft_print_int_width(fstr, sign + 2, fstr->wdth - w);
	}
	ft_check_ox(fstr, sign, 1);
	ft_print_int_prec(fstr, sign + 2, fstr->prec - ord);
	ft_buf_str(x + HEX_LL - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, sign + 2, fstr->wdth - w);
}
