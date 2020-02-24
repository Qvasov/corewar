/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 20:35:05 by laleta            #+#    #+#             */
/*   Updated: 2019/07/01 04:08:50 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_parse_flag(t_prnf *pf, const char **s)
{
	const char		*f;
	const char		f_char[] = " +-#0";
	const uint32_t	f_bit[] = {F_SP, F_PL, F_MI, F_PO, F_ZE, 0};

	while (**s && ((f = ft_strchr(f_char, **s)) != NULL))
	{
		pf->flags |= f_bit[f - f_char];
		++(*s);
	}
}

static void	ft_parse_width(t_prnf *pf, const char **s, va_list *ap)
{
	if (**s && ft_isdigit(**s) && *(*s + 1) == '*')
		++(*s);
	if (**s == '*')
	{
		pf->width = va_arg(*ap, int);
		if (pf->width < 0)
		{
			pf->width = -pf->width;
			pf->flags |= F_MI;
		}
		++(*s);
	}
	if (**s && ft_isdigit(**s))
	{
		pf->width = 0;
		while (ft_isdigit(**s))
		{
			pf->width = pf->width * 10 + **s - '0';
			++(*s);
		}
		if (pf->width > INT_MAX)
			pf->width = 0;
	}
}

static void	ft_parse_prec(t_prnf *pf, const char **s, va_list *ap)
{
	if (**s && **s != '.')
	{
		if (pf->prec != 0)
			pf->prec = -1;
	}
	else if (**s && *++(*s) == '*')
	{
		pf->prec = va_arg(*ap, int);
		++(*s);
	}
	else if (**s)
	{
		pf->prec = 0;
		while (ft_isdigit(**s))
		{
			pf->prec = pf->prec * 10 + **s - '0';
			++(*s);
		}
	}
}

static void	ft_parse_size(t_prnf *pf, const char **s)
{
	if (**s && ft_strchr("hlLjz", **s))
	{
		pf->size = **s && !pf->size && ft_strchr("hlLjz", **s) ? *(*s)++ : '\0';
		pf->size2 = **s && !pf->size2 && ft_strchr("hljz", **s) ?
																*(*s)++ : '\0';
		pf->size3 = **s && ft_strchr("hljz", **s) ? *(*s)++ : '\0';
		pf->size4 = **s && ft_strchr("hljz", **s) ? *(*s)++ : '\0';
		if (pf->size && pf->size != 'L')
		{
			pf->size = pf->size2 > pf->size ? pf->size2 : pf->size;
			pf->size = pf->size3 > pf->size ? pf->size3 : pf->size;
			pf->size = pf->size4 > pf->size ? pf->size4 : pf->size;
		}
	}
}

void		ft_parse_fmt_specfr(t_prnf *pf, const char **s, va_list *ap)
{
	ft_parse_flag(pf, s);
	ft_parse_width(pf, s, ap);
	ft_parse_prec(pf, s, ap);
	ft_parse_size(pf, s);
}
