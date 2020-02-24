/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_float_e.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 04:46:00 by laleta            #+#    #+#             */
/*   Updated: 2019/07/01 05:03:15 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_put_exp(t_prnf *pf, char type, char *buf, int16_t exp)
{
	buf = &pf->s[pf->n1];
	if (type == 'a' || type == 'A')
		type = type == 'A' ? 'P' : 'p';
	*buf++ = type;
	*buf++ = exp >= 0 ? '+' : '-';
	if (exp < 0)
		exp = -exp;
	if (exp >= 100)
	{
		if (exp >= 1000)
		{
			*buf++ = exp / 1000 + '0';
			exp %= 1000;
		}
		*buf++ = exp / 100 + '0';
		exp %= 100;
	}
	if ((type != 'p' && type != 'P') ||
								((exp >= 10) && (type == 'p' || type == 'P')))
		*buf++ = exp / 10 + '0';
	exp %= 10;
	*buf++ = exp + '0';
	pf->n2 = buf - &pf->s[pf->n1];
}

void		ft_gen_e(t_prnf *pf, char type, char *buf, int16_t *exp_dig)
{
	int16_t exp;
	int16_t sdig;

	exp = exp_dig[0];
	sdig = exp_dig[1];
	if (type == 'g' || type == 'G')
	{
		if (sdig < pf->prec && !(pf->flags & F_PO))
			pf->prec = sdig;
		if (--pf->prec < 0)
			pf->prec = 0;
		type = type == 'g' ? 'e' : 'E';
	}
	pf->s[pf->n1++] = *buf++;
	if (pf->prec > 0 || pf->flags & F_PO)
		pf->s[pf->n1++] = POINT;
	if (pf->prec > 0)
	{
		if (pf->prec < --sdig)
			sdig = pf->prec;
		ft_memcpy(&pf->s[pf->n1], buf, sdig);
		pf->n1 += sdig;
		pf->nz1 = pf->prec - sdig;
	}
	ft_put_exp(pf, type, buf, exp);
}
