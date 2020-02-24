/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 23:32:02 by ddarell           #+#    #+#             */
/*   Updated: 2019/12/01 23:32:03 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_color(char *format, t_fstr *fstr)
{
	if ((ft_strncmp(format, "{EOC}", 5)) == 0)
		ft_buf_str_full("\033[0m", 4, fstr);
	else if ((ft_strncmp(format, "{RED}", 5)) == 0)
		ft_buf_str_full("\033[31m", 5, fstr);
	else if ((ft_strncmp(format, "{GRE}", 5)) == 0)
		ft_buf_str_full("\033[32m", 5, fstr);
	else if ((ft_strncmp(format, "{YEL}", 5)) == 0)
		ft_buf_str_full("\033[33m", 5, fstr);
	else if ((ft_strncmp(format, "{BLU}", 5)) == 0)
		ft_buf_str_full("\033[34m", 5, fstr);
	else if ((ft_strncmp(format, "{PUR}", 5)) == 0)
		ft_buf_str_full("\033[35m", 5, fstr);
	else
	{
		ft_buf_smb('{', 1, fstr);
		return (1);
	}
	return (5);
}
