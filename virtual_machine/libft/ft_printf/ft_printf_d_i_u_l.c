/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d_i_u_l.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:56:10 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 15:56:21 by ddarell          ###   ########.fr       */
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
		*(dig + i) = (char)(a % 10) + '0';
		a /= 10;
	}
	return (size - i);
}

static void	check_sign(t_fstr *fstr, char *sign)
{
	if (fstr->uni.lin < 0)
	{
		*sign = '-';
		fstr->uni.ulin = (unsigned long int)(~(fstr->uni.lin) + 1);
	}
	else
	{
		fstr->uni.ulin = (unsigned long int)fstr->uni.lin;
		if (ft_flag(fstr->flag, PLUS))
			*sign = '+';
		else if (ft_flag(fstr->flag, SPACE))
			*sign = ' ';
		else
			*sign = 0;
	}
}

void		ft_printf_d_i_l(t_fstr *fstr, va_list *arg)
{
	char	d_i_l[DEC_L];
	char	sign;
	int		ord;
	int		w;

	fstr->uni.lin = va_arg(*arg, long int);
	check_sign(fstr, &sign);
	ord = put_digit_l(d_i_l, fstr->uni.ulin, DEC_L);
	ord = (fstr->uni.ulin == 0 && fstr->prec == 0) ? 0 : ord;
	w = ft_max(fstr->prec, ord) + (sign != 0);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
	ft_print_int_prec(fstr, &sign, fstr->prec - ord);
	ft_buf_str(d_i_l + DEC_L - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
}

void		ft_printf_u_l(t_fstr *fstr, va_list *arg)
{
	char	u_l[DEC_UL];
	char	sign;
	int		ord;
	int		w;

	fstr->uni.ulin = va_arg(*arg, unsigned long int);
	sign = 0;
	ord = put_digit_l(u_l, fstr->uni.ulin, DEC_UL);
	ord = (fstr->uni.ulin == 0 && fstr->prec == 0) ? 0 : ord;
	w = ft_max(fstr->prec, ord);
	if (fstr->wdth > w && !(ft_flag(fstr->flag, MINUS)))
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
	ft_print_int_prec(fstr, &sign, fstr->prec - ord);
	ft_buf_str(u_l + DEC_UL - ord, ord, fstr);
	if (fstr->wdth > w)
		ft_print_int_width(fstr, &sign, fstr->wdth - w);
}
