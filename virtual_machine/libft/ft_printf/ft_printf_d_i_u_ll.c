/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d_i_u_ll.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:54:45 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 15:55:09 by ddarell          ###   ########.fr       */
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
		*(dig + i) = (char)(a % 10) + '0';
		a /= 10;
	}
	return (size - i);
}

static void	check_sign(t_fstr *fstr, char *sign)
{
	if (fstr->uni.llin < 0)
	{
		*sign = '-';
		fstr->uni.ullin = (unsigned long long int)(~(fstr->uni.llin) + 1);
	}
	else
	{
		fstr->uni.ullin = (unsigned long long int)fstr->uni.llin;
		if (ft_flag(fstr->flag, PLUS))
			*sign = '+';
		else if (ft_flag(fstr->flag, SPACE))
			*sign = ' ';
		else
			*sign = 0;
	}
}

void		ft_printf_d_i_ll(t_fstr *fstr, va_list *arg)
{
	char	d_i_ll[DEC_LL];
	char	sign;
	int		ord;
	int		w;

	fstr->uni.llin = va_arg(*arg, long long int);
	check_sign(fstr, &sign);
	ord = put_digit_ll(d_i_ll, fstr->uni.ullin, DEC_LL);
	ord = (fstr->uni.ullin == 0 && fstr->prec == 0) ? 0 : ord;
	w = ft_max(fstr->prec, ord) + (sign != 0);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
	ft_print_int_prec(fstr, &sign, fstr->prec - ord);
	ft_buf_str(d_i_ll + DEC_LL - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
}

void		ft_printf_u_ll(t_fstr *fstr, va_list *arg)
{
	char	u_ll[DEC_ULL];
	char	sign;
	int		ord;
	int		w;

	fstr->uni.ullin = va_arg(*arg, unsigned long long int);
	sign = 0;
	ord = put_digit_ll(u_ll, fstr->uni.ullin, DEC_ULL);
	ord = (fstr->uni.ullin == 0 && fstr->prec == 0) ? 0 : ord;
	w = ft_max(fstr->prec, ord);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
	ft_print_int_prec(fstr, &sign, fstr->prec - ord);
	ft_buf_str(u_ll + DEC_ULL - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
}
