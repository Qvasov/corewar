/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_type_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 00:55:50 by laleta            #+#    #+#             */
/*   Updated: 2019/06/24 02:23:35 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "pf_errno.h"

void				ft_type_m(char type, char *buf, t_prnf *pf, va_list *ap)
{
	if (errno > 70 || errno < 0)
		errno = 0;
	pf->s = g_errno_tab[errno];
	pf->n1 = ft_strlen(pf->s);
	if ((pf->flags & (F_ZE | F_MI)) == F_ZE)
		pf->nz0 = pf->width - pf->n1;
	(void)buf;
	(void)type;
	(void)ap;
}

void				ft_type_c(char type, char *buf, t_prnf *pf, va_list *ap)
{
	uint32_t		wc;

	if (pf->flags & F_ZE)
		pf->nz0 = --pf->width;
	if (type == 'C' || pf->size == 'l')
	{
		pf->s = &buf[pf->n1];
		wc = va_arg(*ap, int);
		ft_wctoa(pf, &wc, type);
	}
	else
	{
		buf[pf->n1] = va_arg(*ap, int);
		pf->s = &buf[pf->n1];
		pf->n1 = 1;
	}
}

static void			ft_type_s_l(char type, char *buf, t_prnf *pf, uint32_t *wc)
{
	if (type == 'S' || pf->size == 'l' || type == 'R')
	{
		pf->s = &buf[pf->n0];
		ft_wctoa(pf, wc, type);
	}
	else
	{
		pf->n1 = ft_strlen(pf->s);
		if (pf->prec >= 0 && pf->prec < pf->n1)
			pf->n1 = pf->prec;
	}
	if (type == 'r' || type == 'R')
	{
		ft_type_r(type, pf, 0, 0);
		pf->n1 = ft_strlen(pf->s);
		if (pf->prec >= 0 && pf->prec < pf->n1)
			pf->n1 = pf->prec;
	}
}

void				ft_type_s_r(char type, char *buf, t_prnf *pf, va_list *ap)
{
	uint32_t		*wc;

	if (type == 'S' || pf->size == 'l' || type == 'R')
		wc = (unsigned int*)va_arg(*ap, wchar_t *);
	else
		pf->s = va_arg(*ap, char *);
	if ((pf->s == NULL && (type == 's' || type == 'r') && pf->size != 'l') ||
		(wc == NULL && (type == 'S' || pf->size == 'l' || type == 'R')))
	{
		if (!(pf->flags & F_ZE))
		{
			pf->s = "(null)";
			pf->n1 = 6;
			pf->n1 = pf->prec < pf->n1 && pf->prec >= 0 ? pf->prec : 6;
		}
	}
	else
		ft_type_s_l(type, buf, pf, wc);
	if ((pf->flags & (F_ZE | F_MI)) == F_ZE)
		pf->nz0 = pf->width - pf->n1;
	(void)buf;
}
