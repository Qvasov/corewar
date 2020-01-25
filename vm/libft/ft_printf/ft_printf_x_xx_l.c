/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x_xx_l.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:38:54 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 15:38:58 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_digit_l(char *dig, unsigned long int a, int size, char *base)
{
	int i;

	i = size;
	while (a || i == size)
	{
		--i;
		*(dig + i) = *(base + (a & 15));
		a = a >> 4;
	}
	return (size - i);
}

void		ft_printf_x_l(t_fstr *fstr, va_list *arg)
{
	char	x_l[HEX_L];
	char	sign[3];
	int		ord;
	int		w;
	char	base[17];

	ft_strcpy(base, "0123456789abcdef");
	fstr->uni.ulin = va_arg(*arg, unsigned long int);
	ft_set_sign_x(fstr, sign);
	ord = put_digit_l(x_l, fstr->uni.ulin, HEX_L, base);
	ord = (fstr->uni.ulin == 0 && fstr->prec == 0) ? 0 : ord;
	w = ft_max(fstr->prec, ord) + 2 * (sign[0] != 0);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
	{
		ft_check_ox(fstr, sign, 0);
		ft_print_int_width(fstr, sign + 2, fstr->wdth - w);
	}
	ft_check_ox(fstr, sign, 1);
	ft_print_int_prec(fstr, sign + 2, fstr->prec - ord);
	ft_buf_str(x_l + HEX_L - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, sign + 2, fstr->wdth - w);
}

void		ft_printf_xx_l(t_fstr *fstr, va_list *arg)
{
	char	xx_l[HEX_L];
	char	sign[3];
	int		ord;
	int		w;
	char	base[17];

	ft_strcpy(base, "0123456789ABCDEF");
	fstr->uni.ulin = va_arg(*arg, unsigned long int);
	ft_set_sign_xx(fstr, sign);
	ord = put_digit_l(xx_l, fstr->uni.ulin, HEX_L, base);
	ord = (fstr->uni.ulin == 0 && fstr->prec == 0) ? 0 : ord;
	w = ft_max(fstr->prec, ord) + 2 * (sign[0] != 0);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
	{
		ft_check_ox(fstr, sign, 0);
		ft_print_int_width(fstr, sign + 2, fstr->wdth - w);
	}
	ft_check_ox(fstr, sign, 1);
	ft_print_int_prec(fstr, sign + 2, fstr->prec - ord);
	ft_buf_str(xx_l + HEX_L - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, sign + 2, fstr->wdth - w);
}
