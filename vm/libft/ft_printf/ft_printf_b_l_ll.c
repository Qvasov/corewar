/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_b_l_ll.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 21:08:01 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/29 21:08:25 by ddarell          ###   ########.fr       */
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
		*(dig + i) = (char)((a & 1) + '0');
		a = a >> 1;
	}
	return (size - i);
}

static int	put_digit_ll(char *dig, unsigned long long int a, int size)
{
	int i;

	i = size;
	while (a || i == size)
	{
		--i;
		*(dig + i) = (char)((a & 1) + '0');
		a = a >> 1;
	}
	return (size - i);
}

void		ft_printf_b_l(t_fstr *fstr, va_list *arg)
{
	char	b_l[BIN_L];
	char	sign;
	int		ord;
	int		w;

	fstr->uni.ulin = va_arg(*arg, unsigned long int);
	ord = put_digit_l(b_l, fstr->uni.ulin, BIN_L);
	ord = (fstr->uni.ulin == 0 && fstr->prec == 0) ? 0 : ord;
	sign = 0;
	w = ft_max(fstr->prec, ord);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
	ft_print_int_prec(fstr, &sign, fstr->prec - ord);
	ft_buf_str(b_l + BIN_L - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
}

void		ft_printf_b_ll(t_fstr *fstr, va_list *arg)
{
	char	b_ll[BIN_LL];
	char	sign;
	int		ord;
	int		w;

	fstr->uni.ullin = va_arg(*arg, unsigned long long int);
	ord = put_digit_ll(b_ll, fstr->uni.ullin, BIN_LL);
	ord = (fstr->uni.ullin == 0 && fstr->prec == 0) ? 0 : ord;
	sign = 0;
	w = ft_max(fstr->prec, ord);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
	ft_print_int_prec(fstr, &sign, fstr->prec - ord);
	ft_buf_str(b_ll + BIN_LL - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
}
