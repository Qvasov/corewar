/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_hex_alpha.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:55:02 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 14:55:19 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_set_sign_x(t_fstr *fstr, char *sign)
{
	if (ft_flag(fstr->flag, HASH) && fstr->uni.uin != 0)
	{
		*sign = '0';
		*(sign + 1) = 'x';
	}
	else
	{
		*sign = 0;
		*(sign + 1) = 0;
	}
	*(sign + 2) = 0;
}

void	ft_set_sign_xx(t_fstr *fstr, char *sign)
{
	if (ft_flag(fstr->flag, HASH) && fstr->uni.uin != 0)
	{
		*sign = '0';
		*(sign + 1) = 'X';
	}
	else
	{
		*sign = 0;
		*(sign + 1) = 0;
	}
	*(sign + 2) = 0;
}
