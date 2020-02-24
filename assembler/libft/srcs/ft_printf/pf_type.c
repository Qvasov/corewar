/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 01:37:57 by laleta            #+#    #+#             */
/*   Updated: 2019/06/30 22:08:10 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "pf_time.h"

void	ft_type_k(char type, char *buf, t_prnf *pf, va_list *ap)
{
	ft_ttoa(&buf);
	pf->s = &buf[0];
	pf->n1 = ft_strlen(pf->s);
	(void)type;
	(void)ap;
}

void	ft_type_n(char type, char *buf, t_prnf *pf, va_list *ap)
{
	if (pf->size == 'h')
		*va_arg(*ap, short *) = pf->nchar;
	else if (pf->size != 'l')
		*va_arg(*ap, int *) = pf->nchar;
	else
		*va_arg(*ap, long *) = pf->nchar;
	(void)type;
	(void)buf;
}

void	ft_type_p(char type, char *buf, t_prnf *pf, va_list *ap)
{
	pf->nbr.i = (long)va_arg(*ap, void *);
	buf[pf->n0++] = '0';
	buf[pf->n0++] = 'x';
	pf->s = &buf[pf->n0];
	ft_itoa_base(pf, 'x');
	(void)type;
}

void	ft_type_proc(char type, char *buf, t_prnf *pf, va_list *ap)
{
	if ((pf->flags & (F_ZE | F_MI)) == F_ZE)
		pf->nz0 = --pf->width;
	buf[pf->n1++] = '%';
	pf->s = &buf[pf->n0];
	(void)type;
	(void)ap;
}

void	ft_type_undef(char type, char *buf, t_prnf *pf, va_list *ap)
{
	if (pf->flags & F_ZE)
		pf->nz0 = --pf->width;
	buf[pf->n1++] = type;
	pf->s = &buf[pf->n0];
	(void)buf;
	(void)ap;
}
