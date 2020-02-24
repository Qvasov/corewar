/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buff_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:03:41 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 16:04:04 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_check_ox(t_fstr *fstr, char *sign, char flag)
{
	if (flag == 0 && *sign && fstr->prec < 0 && !(ft_flag(fstr->flag, MINUS))
		&& ft_flag(fstr->flag, NOLL))
	{
		ft_buf_str(sign, 2, fstr);
		*sign = 0;
		return ;
	}
	else if (flag == 1 && *sign)
	{
		ft_buf_str(sign, 2, fstr);
		*sign = 0;
	}
}

void	ft_print_int_width(t_fstr *fstr, char *sign, int len)
{
	char symb;

	symb = (fstr->prec >= 0 || ft_flag(fstr->flag, MINUS)
		|| !(ft_flag(fstr->flag, NOLL))) ? ' ' : '0';
	if (symb == '0' && *sign)
	{
		ft_buf_smb(*sign, 1, fstr);
		*sign = 0;
	}
	if (len > 0)
		ft_buf_smb(symb, len, fstr);
	fstr->wdth = 0;
}

void	ft_print_int_prec(t_fstr *fstr, char *sign, int len)
{
	if (*sign)
	{
		ft_buf_smb(*sign, 1, fstr);
		*sign = 0;
	}
	if (len > 0)
		ft_buf_smb('0', len, fstr);
}
