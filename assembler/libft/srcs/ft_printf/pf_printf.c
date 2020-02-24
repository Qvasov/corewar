/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 23:09:16 by laleta            #+#    #+#             */
/*   Updated: 2019/07/01 04:08:04 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char g_spac[] = "                                ";
static char g_zero[] = "00000000000000000000000000000000";

static inline int	ft_put_char(t_wr_fun *wr, t_prnf *pf, const char *s, int n)
{
	if (n > 0)
	{
		if ((wr->arg = (*wr->f)(wr->arg, s, n)) != NULL)
			pf->nchar += n;
		else
			return (0);
	}
	return (1);
}

static inline void	ft_put_fill(t_wr_fun *wr, t_prnf *pf, const char *s, int n)
{
	int	i;
	int	j;

	if (n > 0)
	{
		j = n;
		while (j > 0)
		{
			i = j > 32 ? 32 : j;
			ft_put_char(wr, pf, s, i);
			j -= i;
		}
	}
}

static int32_t		ft_put(t_prnf *pf, t_wr_fun *wr, char *buf)
{
	pf->width -= pf->n0 + pf->nz0 + pf->n1 + pf->nz1 + pf->n2 + pf->nz2;
	if (!(pf->flags & F_MI))
		ft_put_fill(wr, pf, g_spac, pf->width);
	if (!ft_put_char(wr, pf, buf, pf->n0))
		return (0);
	ft_put_fill(wr, pf, g_zero, pf->nz0);
	if (!ft_put_char(wr, pf, pf->s, pf->n1))
		return (0);
	ft_put_fill(wr, pf, g_zero, pf->nz1);
	if (!ft_put_char(wr, pf, pf->s + pf->n1, pf->n2))
		return (0);
	ft_put_fill(wr, pf, g_zero, pf->nz2);
	if (pf->flags & F_MI)
		ft_put_fill(wr, pf, g_spac, pf->width);
	return (1);
}

static inline void	ft_find_proc(const char **s, const char *fmt, t_prnf *pf)
{
	pf->flags = 0;
	pf->prec = -1;
	pf->width = 0;
	pf->size = '\0';
	pf->size2 = '\0';
	pf->n0 = 0;
	pf->nz0 = 0;
	pf->n1 = 0;
	pf->nz1 = 0;
	pf->n2 = 0;
	pf->nz2 = 0;
	*s = fmt;
	while (**s)
	{
		if (**s == '%')
			return ;
		(*s)++;
	}
}

int32_t				ft_prnf(t_wr_fun *wr, const char *fmt, va_list *ap,
																	t_prnf *pf)
{
	int32_t		ret;
	char		buf[16400];
	const char	*s;

	while (1)
	{
		ft_find_proc(&s, fmt, pf);
		if (!ft_put_char(wr, pf, fmt, s - fmt))
			return (-1);
		if (*s == '\0')
			return (pf->nchar);
		fmt = ++s;
		ft_parse_fmt_specfr(pf, &s, ap);
		while (*s && ft_strchr("hlLjz -+0#.", *s))
			ft_parse_fmt_specfr(pf, &s, ap);
		if ((ret = ft_putbuf(pf, ap, *s, buf)) == 0)
			return (pf->nchar);
		else if (ret == -1)
			return (-1);
		if (!ft_put(pf, wr, buf))
			return (-1);
		fmt = s + 1;
	}
}
