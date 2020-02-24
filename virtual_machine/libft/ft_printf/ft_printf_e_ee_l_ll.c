/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_e_ee_l_ll.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 21:04:51 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/29 21:04:53 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_e_ord_in_array(int e, char symb, char *exp)
{
	char	sign;
	int		ord;

	if (e < 0)
	{
		e = -e;
		sign = '-';
	}
	else
		sign = '+';
	ord = ft_put_digit_dec(exp + 2, e, 4);
	if (ord < 2)
	{
		exp[4] = '0';
		ord++;
	}
	exp[4 - ord] = symb;
	exp[5 - ord] = sign;
	return (ord + 2);
}

static int	put_ldouble_in_array(char *res, t_dbl *dbl,
									t_fstr *fstr, char *e_arr)
{
	unsigned long long	mnt;
	int					exp;
	int					e_ord;

	mnt = dbl->udbl.ldbl.lull;
	exp = (int)((unsigned int)0x7fff & dbl->udbl.ldbl.li);
	ft_check_double_exc((!exp || !mnt) + 2 * (exp == 0x7fff),
			mnt & (unsigned long long)0x7fffffffffffffff, fstr, dbl);
	if (dbl->exc > 2)
		return (0);
	else if (dbl->exc == 2)
	{
		if ((fstr->flag) >> TYPE == 38)
			return (put_e_ord_in_array(0, 'e', e_arr));
		return (put_e_ord_in_array(0, 'E', e_arr));
	}
	*res = 0;
	res++;
	ft_ldtoa_to_array(dbl, exp, mnt);
	e_ord = dbl->ord;
	dbl->ord = 0;
	ft_approx_double(res, dbl, fstr->prec);
	if ((fstr->flag) >> TYPE == 38)
		return (put_e_ord_in_array(e_ord, 'e', e_arr));
	return (put_e_ord_in_array(e_ord, 'E', e_arr));
}

void		ft_printf_e_ee_ll(t_fstr *fstr, va_list *arg)
{
	t_dbl	dbl;
	int		wid;
	int		e_ord;
	char	array[LD_LIMIT_E + LD_LIMIT_M + 3];
	char	e_arr[6];

	dbl.res = array;
	dbl.udbl.llf = va_arg(*arg, long double);
	ft_check_double_sign_n_prec(fstr, &dbl,
								((0x8000) & dbl.udbl.ldbl.li) >> 15);
	e_ord = put_ldouble_in_array(dbl.res, &dbl, fstr, e_arr);
	if (!e_ord && (fstr->flag) >> TYPE == 40)
		ft_strcapitalize(dbl.res);
	wid = ft_check_double_width_n_point(fstr, &dbl) + e_ord;
	if (fstr->wdth > wid && !(ft_flag(fstr->flag, MINUS)))
		ft_buff_double_width(fstr, &dbl.sign, fstr->wdth - wid);
	ft_buff_double(fstr, dbl.res + (dbl.res[0] == 0), &dbl);
	if (e_ord)
		ft_buf_str(e_arr + 6 - e_ord, e_ord, fstr);
	if (fstr->wdth > wid)
		ft_buff_double_width(fstr, &dbl.sign, fstr->wdth - wid);
}

static int	put_double_in_array(char *res, t_dbl *dbl,
								t_fstr *fstr, char *e_arr)
{
	unsigned long long	mnt;
	int					exp;
	int					e_ord;

	mnt = ((unsigned long long)0x000fffffffffffff) & dbl->udbl.ull;
	exp = (int)(((unsigned long long)0x7ff0000000000000 & dbl->udbl.ull) >> 52);
	ft_check_double_exc((exp == 0) + 2 * (exp == 0x7ff), mnt, fstr, dbl);
	if (dbl->exc > 2)
		return (0);
	else if (dbl->exc == 2)
	{
		if ((fstr->flag) >> TYPE == 37)
			return (put_e_ord_in_array(0, 'e', e_arr));
		return (put_e_ord_in_array(0, 'E', e_arr));
	}
	*res = 0;
	res++;
	ft_dtoa_to_array(dbl, exp, mnt);
	e_ord = dbl->ord;
	dbl->ord = 0;
	ft_approx_double(res, dbl, fstr->prec);
	if ((fstr->flag) >> TYPE == 37)
		return (put_e_ord_in_array(e_ord, 'e', e_arr));
	return (put_e_ord_in_array(e_ord, 'E', e_arr));
}

void		ft_printf_e_ee_l(t_fstr *fstr, va_list *arg)
{
	t_dbl	dbl;
	int		wid;
	int		e_ord;
	char	array[D_LIMIT_E + D_LIMIT_M + 3];
	char	e_arr[6];

	dbl.res = array;
	dbl.udbl.lf = va_arg(*arg, double);
	ft_check_double_sign_n_prec(fstr, &dbl,
								((0x8000000000000000) & dbl.udbl.ull) >> 63);
	e_ord = put_double_in_array(dbl.res, &dbl, fstr, e_arr);
	if (!e_ord && (fstr->flag) >> TYPE == 39)
		ft_strcapitalize(dbl.res);
	wid = ft_check_double_width_n_point(fstr, &dbl) + e_ord;
	if (fstr->wdth > wid && !(ft_flag(fstr->flag, MINUS)))
		ft_buff_double_width(fstr, &dbl.sign, fstr->wdth - wid);
	ft_buff_double(fstr, dbl.res + (dbl.res[0] == 0), &dbl);
	if (e_ord)
		ft_buf_str(e_arr + 6 - e_ord, e_ord, fstr);
	if (fstr->wdth > wid)
		ft_buff_double_width(fstr, &dbl.sign, fstr->wdth - wid);
}
