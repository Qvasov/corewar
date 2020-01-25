/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:56:56 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 15:56:57 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_char(t_fstr *fstr, va_list *arg)
{
	char c;

	c = (char)va_arg(*arg, int);
	if (fstr->wdth > 1 && !(ft_flag(fstr->flag, MINUS)))
		ft_print_str_width(fstr, 1);
	ft_buf_smb(c, 1, fstr);
	if (fstr->wdth > 1)
		ft_print_str_width(fstr, 1);
}
