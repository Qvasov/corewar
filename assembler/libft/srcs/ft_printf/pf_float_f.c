/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_float_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 02:50:07 by laleta            #+#    #+#             */
/*   Updated: 2019/07/01 05:03:14 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static inline void	ft_fractional(t_prnf *pf, char *buf, int16_t sdig,
																	int16_t exp)
{
	pf->s[pf->n1++] = '0';
	if (pf->prec > 0 || pf->flags & F_PO)
		pf->s[pf->n1++] = POINT;
	if (pf->prec < -exp)
		exp = -pf->prec;
	pf->nz1 = -exp;
	pf->prec += exp;
	if (pf->prec < sdig)
		sdig = pf->prec;
	ft_memcpy(&pf->s[pf->n1], buf, pf->n2 = sdig);
	pf->nz2 = pf->prec - sdig;
}

static inline void	ft_whole(t_prnf *pf, char *buf, int16_t sdig, int16_t exp)
{
	ft_memcpy(&pf->s[pf->n1], buf, sdig);
	pf->n1 += sdig;
	pf->nz1 = exp - sdig;
	if (pf->prec > 0 || pf->flags & F_PO)
	{
		pf->s[pf->n1] = POINT;
		++pf->n2;
	}
	pf->nz2 = pf->prec;
}

static inline void	ft_mixed(t_prnf *pf, char *buf, int16_t sdig, int16_t exp)
{
	ft_memcpy(&pf->s[pf->n1], buf, exp);
	pf->n1 += exp;
	sdig -= exp;
	if (pf->prec > 0 || pf->flags & F_PO)
		pf->s[pf->n1++] = POINT;
	if (pf->prec < sdig)
		sdig = pf->prec;
	ft_memcpy(&pf->s[pf->n1], buf + exp, sdig);
	pf->n1 += sdig;
	pf->nz1 = pf->prec - sdig;
}

void				ft_gen_f(t_prnf *pf, char type, char *buf, int16_t *exp_dig)
{
	int16_t	exp;
	int16_t	sdig;

	exp = exp_dig[0];
	sdig = exp_dig[1];
	++exp;
	if (type != 'f' && type != 'F')
	{
		if (!(pf->flags & F_PO) && sdig < pf->prec)
			pf->prec = sdig;
		if ((pf->prec -= exp) < 0)
			pf->prec = 0;
	}
	if (exp <= 0)
		ft_fractional(pf, buf, sdig, exp);
	else if (sdig < exp)
		ft_whole(pf, buf, sdig, exp);
	else
		ft_mixed(pf, buf, sdig, exp);
}
