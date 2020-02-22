/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprint_not_format.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 23:31:55 by ddarell           #+#    #+#             */
/*   Updated: 2020/02/21 14:15:08 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_fprint_not_format(char *format, t_fstr *fstr)
{
	int i;

	i = 0;
	while (format[i] && format[i] != '%')
		i++;
	ft_buf_str(format, i, fstr);
	return (i);
}

int	ft_print_not_format(char *format, t_fstr *fstr)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = format;
	while (format[i] && format[i] != '%')
	{
		while (format[i] && format[i] != '%' && format[i] != '{')
			i++;
		if (format[i] == '{')
		{
			ft_buf_str(format, i, fstr);
			format += i;
			i = 0;
			format += ft_check_color(format, fstr);
		}
	}
	ft_buf_str(format, i, fstr);
	return ((int)(format - tmp + i));
}
