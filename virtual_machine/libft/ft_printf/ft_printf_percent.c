/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_percent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:41:46 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 15:46:10 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_percent(t_fstr *fstr, va_list *arg)
{
	arg = NULL;
	if (fstr->wdth > 1 && !(ft_flag(fstr->flag, MINUS)))
		ft_print_str_width(fstr, 1);
	ft_buf_smb('%', 1, fstr);
	if (fstr->wdth > 1)
		ft_print_str_width(fstr, 1);
}
