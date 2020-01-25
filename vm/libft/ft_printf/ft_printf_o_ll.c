/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_o_ll.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:48:19 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 15:48:20 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_digit_ll(char *dig, unsigned long long int a, int size)
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
		if (fstr->uni.ullin == 0)
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

void		ft_printf_o_ll(t_fstr *fstr, va_list *arg)
{
	char	o_ll[OCT_LL];
	char	sign;
	int		ord;
	int		w;

	fstr->uni.ullin = va_arg(*arg, unsigned long long int);
	ord = put_digit_ll(o_ll, fstr->uni.ullin, OCT_LL);
	ord = (fstr->uni.ullin == 0 && fstr->prec == 0) ? 0 : ord;
	check_sign(fstr, &sign, ord);
	w = ft_max(fstr->prec, ord) + (sign != 0);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
	ft_print_int_prec(fstr, &sign, fstr->prec - ord);
	ft_buf_str(o_ll + OCT_LL - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
}
