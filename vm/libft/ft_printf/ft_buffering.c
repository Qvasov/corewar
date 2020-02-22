/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffering.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:03:11 by ddarell           #+#    #+#             */
/*   Updated: 2020/02/21 17:04:11 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_buf_print(t_fstr *fstr)
{
	if ((write(fstr->sfd, fstr->buf, fstr->idx)) == -1)
	{
		fstr->prin = -1;
		exit(0);
	}
	fstr->prin += fstr->idx;
	fstr->idx = 0;
}

void	ft_buf_str(char *str, int size, t_fstr *fstr)
{
	while (size > 0)
	{
		while (fstr->idx < BUF_SIZE && size > 0)
		{
			fstr->buf[fstr->idx] = *str;
			fstr->idx++;
			str++;
			size--;
		}
		if (size > 0)
			ft_buf_print(fstr);
	}
}

void	ft_buf_smb(char smb, int size, t_fstr *fstr)
{
	while (size > 0)
	{
		while (fstr->idx < BUF_SIZE && size > 0)
		{
			fstr->buf[fstr->idx] = smb;
			fstr->idx++;
			size--;
		}
		if (size > 0)
			ft_buf_print(fstr);
	}
}

void	ft_buf_str_full(char *str, int size, t_fstr *fstr)
{
	if (size > BUF_SIZE)
		return ;
	if (BUF_SIZE - fstr->idx < size)
		ft_buf_print(fstr);
	while (size > 0)
	{
		fstr->buf[fstr->idx] = *str;
		fstr->idx++;
		str++;
		size--;
	}
}
