/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_llf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:48:56 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 15:53:44 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	set_nulls(char *buf, int i)
{
	while (--i >= 0)
	{
		*buf = '0';
		buf++;
	}
}

static int	set_mnt(int exp, unsigned long long *mnt)
{
	unsigned long long	flag;
	unsigned long long	tmp_mnt;
	int					k;

	tmp_mnt = *mnt;
	k = 0;
	flag = (unsigned long long)1 << 63;
	while (tmp_mnt)
	{
		tmp_mnt &= ~flag;
		k++;
		flag = flag >> 1;
	}
	*mnt = *mnt >> (64 - k);
	k--;
	return ((exp != 0) ? exp - 16383 - k : exp - 16382 - k);
}

void		ft_ldtoa_to_array(t_dbl *dbl, int exp, unsigned long long mnt)
{
	int					min_pow;
	char				tmp[LD_LIMIT_E + LD_LIMIT_M + 3];
	unsigned long long	mnt_part_1;
	unsigned long long	mnt_part_2;

	min_pow = set_mnt(exp, &mnt);
	mnt_part_1 = mnt % 100000000000000000;
	mnt_part_2 = mnt / 100000000000000000;
	dbl->ord = ft_bin_pow_array(dbl->res + 1, min_pow);
	if (mnt_part_2)
	{
		set_nulls(tmp, 17);
		ft_strcpy(tmp + 17, dbl->res + 1);
		dbl->ord += ft_rev_mult_array_num(tmp + 17, mnt_part_2) + 17;
		ft_rev_mult_array_num(dbl->res + 1, mnt_part_1);
		dbl->ord += ft_rev_sum_array_array(dbl->res + 1, tmp);
	}
	else
		dbl->ord += ft_rev_mult_array_num(dbl->res + 1, mnt_part_1);
	ft_reverse_str(dbl->res + 1);
}

static void	put_ldouble_in_array(char *res, t_dbl *dbl, t_fstr *fstr)
{
	unsigned long long	mnt;
	int					exp;

	mnt = dbl->udbl.ldbl.lull;
	exp = (int)((unsigned int)0x7fff & dbl->udbl.ldbl.li);
	ft_check_double_exc((!exp || !mnt) + 2 * (exp == 0x7fff),
					mnt & (unsigned long long)0x7fffffffffffffff, fstr, dbl);
	if (dbl->exc > 1)
		return ;
	*res = 0;
	res++;
	ft_ldtoa_to_array(dbl, exp, mnt);
	ft_approx_double(res, dbl, fstr->prec);
}

void		ft_printf_f_ll(t_fstr *fstr, va_list *arg)
{
	t_dbl	dbl;
	int		wid;
	char	array[LD_LIMIT_E + LD_LIMIT_M + 3];

	dbl.res = array;
	dbl.udbl.llf = va_arg(*arg, long double);
	ft_check_double_sign_n_prec(fstr, &dbl,
								((0x8000) & dbl.udbl.ldbl.li) >> 15);
	put_ldouble_in_array(dbl.res, &dbl, fstr);
	wid = ft_check_double_width_n_point(fstr, &dbl);
	if (fstr->wdth > wid && !(ft_flag(fstr->flag, MINUS)))
		ft_buff_double_width(fstr, &dbl.sign, fstr->wdth - wid);
	ft_buff_double(fstr, dbl.res + (dbl.res[0] == 0), &dbl);
	if (fstr->wdth > wid)
		ft_buff_double_width(fstr, &dbl.sign, fstr->wdth - wid);
}
