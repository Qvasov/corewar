/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:33:30 by ddarell           #+#    #+#             */
/*   Updated: 2019/12/02 19:31:18 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	match_fstr(t_fstr *fstr, char *current, va_list *arg)
{
	char *tmp;

	tmp = NULL;
	while (tmp != current)
	{
		tmp = current;
		current = current + ft_match_flags(fstr, current);
		current = current + ft_match_width(fstr, current, arg);
		current = current + ft_match_prec(fstr, current, arg);
		current = current + ft_match_length(fstr, current);
		fstr->strl += (int)(current - tmp);
	}
	ft_match_type(fstr, current);
}

static int	print_not_format(char *format, t_fstr *fstr)
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

static void	print_format(t_fstr *fstr, char *start,
						va_list *arg, void (**f)(t_fstr *, va_list *))
{
	int type_num;

	ft_set_fstr(fstr);
	match_fstr(fstr, start, arg);
	type_num = (fstr->flag >> TYPE);
	if (type_num > 0)
		f[type_num](fstr, arg);
}

int			ft_printf(const char *format, ...)
{
	va_list arg;
	t_fstr	fstr;
	void	(*func[41])(t_fstr *, va_list *arg);

	if (format == NULL)
		return (-1);
	ft_init_n_set(func, &fstr);
	va_start(arg, format);
	while (*format)
	{
		if (*format == '%')
		{
			print_format(&fstr, (char *)format + 1, &arg, func);
			format = format + fstr.strl;
		}
		else
			format = format + print_not_format((char *)format, &fstr);
	}
	ft_buf_print(&fstr);
	va_end(arg);
	return (fstr.prin);
}

int			ft_fprintf(int fd, const char *format, ...)
{
	va_list arg;
	t_fstr	fstr;
	void	(*func[41])(t_fstr *, va_list *arg);

	if (format == NULL || fd < 0 || fd > MAX_FD)
		return (-1);
	ft_init_n_set(func, &fstr);
	fstr.sfd = fd;
	va_start(arg, format);
	while (*format)
	{
		if (*format == '%')
		{
			print_format(&fstr, (char *)format + 1, &arg, func);
			format = format + fstr.strl;
		}
		else
			format = format + ft_fprint_not_format((char *)format, &fstr);
	}
	ft_buf_print(&fstr);
	va_end(arg);
	return (fstr.prin);
}
