/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_double_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:55:29 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 14:56:44 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_check_double_width_n_point(t_fstr *fstr, t_dbl *dbl)
{
	if (fstr->prec > 0 || ft_flag(fstr->flag, HASH))
		dbl->point = '.';
	else
		dbl->point = 0;
	return (fstr->prec + (dbl->point != 0)
			+ (dbl->ord > 0) * dbl->ord
			+ (dbl->sign != 0) + 1);
}

static void	check_max_exp(unsigned long long int mant, t_fstr *fstr, t_dbl *dbl)
{
	if (mant != 0)
	{
		dbl->exc = 3;
		ft_strcpy(dbl->res, "nan");
		dbl->sign = 0;
	}
	else
	{
		dbl->exc = 3;
		ft_strcpy(dbl->res, "inf");
	}
	dbl->ord = 2;
	dbl->len = 3;
	fstr->prec = 0;
	fstr->flag &= ~((1 << NOLL) | (1 << HASH));
}

static void	check_null_exp(unsigned long long int mant, t_dbl *dbl)
{
	if (mant != 0)
		dbl->exc = 1;
	else
	{
		dbl->exc = 2;
		ft_strcpy(dbl->res, "0");
		dbl->ord = 0;
		dbl->len = 1;
	}
}

void		ft_check_double_exc(int expo_flag,
								unsigned long long int mant,
								t_fstr *fstr, t_dbl *dbl)
{
	dbl->exc = 0;
	if (expo_flag == 1)
		check_null_exp(mant, dbl);
	else if (expo_flag == 2)
		check_max_exp(mant, fstr, dbl);
}

void		ft_check_double_sign_n_prec(t_fstr *fstr, t_dbl *dbl,
										unsigned int sign_bit)
{
	if (sign_bit > 0)
		dbl->sign = '-';
	else
	{
		if (ft_flag(fstr->flag, PLUS))
			dbl->sign = '+';
		else if (ft_flag(fstr->flag, SPACE))
			dbl->sign = ' ';
		else
			dbl->sign = 0;
	}
	if (fstr->prec < 0)
		fstr->prec = 6;
}
