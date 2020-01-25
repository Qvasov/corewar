/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprint_not_format.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 23:31:55 by ddarell           #+#    #+#             */
/*   Updated: 2019/12/01 23:31:56 by ddarell          ###   ########.fr       */
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
