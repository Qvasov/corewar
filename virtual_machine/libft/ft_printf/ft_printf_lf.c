/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_lf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:54:24 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 15:54:35 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	set_mnt(int exp, unsigned long long *mnt)
{
	unsigned long long	flag;
	unsigned long long	tmp_mnt;
	int					k;

	tmp_mnt = *mnt;
	k = 0;
	flag = (unsigned long long)1 << 51;
	while (tmp_mnt)
	{
		tmp_mnt &= ~flag;
		k++;
		flag = flag >> 1;
	}
	*mnt = (*mnt >> (52 - k)) | ((unsigned long long)(exp != 0) << k);
	return ((exp != 0) ? exp - 1023 - k : exp - 1022 - k);
}

void		ft_dtoa_to_array(t_dbl *dbl, int exp, unsigned long long mnt)
{
	int min_pow;

	min_pow = set_mnt(exp, &mnt);
	dbl->ord = ft_bin_pow_array(dbl->res + 1, min_pow);
	dbl->ord += ft_rev_mult_array_num(dbl->res + 1, mnt);
	ft_reverse_str(dbl->res + 1);
}

static void	put_double_in_array(char *res, t_dbl *dbl, t_fstr *fstr)
{
	unsigned long long	mnt;
	int					exp;

	mnt = ((unsigned long long)0x000fffffffffffff) & dbl->udbl.ull;
	exp = (int)(((unsigned long long)0x7ff0000000000000 & dbl->udbl.ull) >> 52);
	ft_check_double_exc((exp == 0) + 2 * (exp == 0x7ff), mnt, fstr, dbl);
	if (dbl->exc > 1)
		return ;
	*res = 0;
	res++;
	ft_dtoa_to_array(dbl, exp, mnt);
	ft_approx_double(res, dbl, fstr->prec);
}

void		ft_printf_f_l(t_fstr *fstr, va_list *arg)
{
	t_dbl	dbl;
	int		wid;
	char	array[D_LIMIT_E + D_LIMIT_M + 3];

	dbl.res = array;
	dbl.udbl.lf = va_arg(*arg, double);
	ft_check_double_sign_n_prec(fstr, &dbl,
								((0x8000000000000000) & dbl.udbl.ull) >> 63);
	put_double_in_array(dbl.res, &dbl, fstr);
	wid = ft_check_double_width_n_point(fstr, &dbl);
	if (fstr->wdth > wid && !(ft_flag(fstr->flag, MINUS)))
		ft_buff_double_width(fstr, &dbl.sign, fstr->wdth - wid);
	ft_buff_double(fstr, dbl.res + (dbl.res[0] == 0), &dbl);
	if (fstr->wdth > wid)
		ft_buff_double_width(fstr, &dbl.sign, fstr->wdth - wid);
}
