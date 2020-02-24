/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 01:41:28 by laleta            #+#    #+#             */
/*   Updated: 2019/06/30 23:49:13 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "pf_buffer.h"

static t_file g_stream =
{
	0, 1, NULL, NULL, &g_stream.buf_1c, &g_stream.buf_1c, 0
};

static void	*ft_writer(void *str, const char *buf, size_t n)
{
	return (ft_fwrite(buf, 1, n, (t_file *)str) == n ? str : NULL);
}

static void	*ft_writestr(void *str, const char *buf, size_t n)
{
	return ((char *)ft_memcpy(str, buf, n) + n);
}

int32_t		ft_printf(const char *fmt, ...)
{
	int			n;
	va_list		ap;
	t_wr_fun	wr;
	t_prnf		pf;
	t_file		*stream;

	if (!fmt)
		return (-1);
	stream = &g_stream;
	pf.nchar = 0;
	wr.f = &ft_writer;
	wr.arg = stream;
	va_start(ap, fmt);
	n = ft_prnf(&wr, fmt, &ap, &pf);
	ft_fflush(stream);
	va_end(ap);
	return (n);
}

int32_t		ft_fprintf(int32_t fd, const char *fmt, ...)
{
	int			n;
	va_list		ap;
	t_wr_fun	wr;
	t_prnf		pf;
	t_file		*stream;

	if (fd != -1 || !fmt)
	{
		stream = &g_stream;
		stream->desc = fd;
		pf.nchar = 0;
		wr.f = &ft_writer;
		wr.arg = stream;
		va_start(ap, fmt);
		n = ft_prnf(&wr, fmt, &ap, &pf);
		ft_fflush(stream);
		va_end(ap);
		return (n);
	}
	return (-1);
}

int32_t		ft_sprintf(char *s, const char *fmt, ...)
{
	int			n;
	va_list		ap;
	t_wr_fun	wr;
	t_prnf		pf;

	if (!fmt || !s)
		return (-1);
	pf.nchar = 0;
	wr.f = &ft_writestr;
	wr.arg = s;
	va_start(ap, fmt);
	n = ft_prnf(&wr, fmt, &ap, &pf);
	if (n >= 0)
		s[n] = '\0';
	va_end(ap);
	return (n);
}
