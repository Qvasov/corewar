/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_o_l.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:48:35 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 15:48:41 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_digit_l(char *dig, unsigned long int a, int size)
{
	int i;

	i = size;
	while (a || i == size)
	{
		--i;
		*(dig + i) = (char)((a & 7) + '0');
		a = a >> 3;
	}
	return (size - i);
}

static void	check_sign(t_fstr *fstr, char *sign, int ord)
{
	if (ft_flag(fstr->flag, HASH))
	{
		if (fstr->uni.ulin == 0)
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

void		ft_printf_o_l(t_fstr *fstr, va_list *arg)
{
	char	o_l[OCT_L];
	char	sign;
	int		ord;
	int		w;

	fstr->uni.ulin = va_arg(*arg, unsigned long int);
	ord = put_digit_l(o_l, fstr->uni.ulin, OCT_L);
	ord = (fstr->uni.ulin == 0 && fstr->prec == 0) ? 0 : ord;
	check_sign(fstr, &sign, ord);
	w = ft_max(fstr->prec, ord) + (sign != 0);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
	ft_print_int_prec(fstr, &sign, fstr->prec - ord);
	ft_buf_str(o_l + OCT_L - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
}
