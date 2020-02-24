/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fwrite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 01:34:07 by laleta            #+#    #+#             */
/*   Updated: 2019/08/06 04:08:39 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "pf_buffer.h"

int32_t					ft_fflush(t_file *str)
{
	int				n;
	unsigned char	*s;

	if (!(str->mode & FW_WRITE))
		return (0);
	s = str->buf;
	while (s < str->next)
	{
		n = write(str->desc, s, str->next - s);
		if (n <= 0)
		{
			str->next = str->buf;
			str->end = str->buf;
			return (-1);
		}
		s += n;
	}
	str->next = str->buf;
	str->end = str->buf_end;
	return (0);
}

static inline int32_t	ft_get_buf(t_file *str)
{
	if (str->next < str->end)
		return (0);
	else if (str->mode & FW_WRITE)
		return (ft_fflush(str));
	if (str->buf)
		;
	else if ((str->buf = (unsigned char *)malloc(FW_BUFSIZ)) == NULL)
	{
		str->buf = &str->buf_1c;
		str->buf_end = str->buf + 1;
	}
	else
		str->buf_end = str->buf + FW_BUFSIZ;
	str->next = str->buf;
	str->end = str->buf_end;
	str->mode |= FW_WRITE;
	return (0);
}

size_t					ft_fwrite(const void *ptr, size_t size, size_t cnt,
																	t_file *str)
{
	char	*s;
	size_t	size_all;
	size_t	m;
	size_t	n;

	s = (char *)ptr;
	size_all = size * cnt;
	if (size_all == 0)
		return (0);
	while (size_all > 0)
	{
		if (str->next < str->end)
			;
		else if (ft_get_buf(str) < 0)
			break ;
		m = size_all;
		n = str->end - str->next;
		if (n < m)
			m = n;
		ft_memcpy(str->next, s, m);
		s += m;
		size_all -= m;
		str->next += m;
	}
	return ((size * cnt - size_all) / size);
}
