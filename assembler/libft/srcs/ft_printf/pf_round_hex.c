/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_round_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 20:36:36 by laleta            #+#    #+#             */
/*   Updated: 2019/07/01 00:29:12 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int16_t	ft_isodd(char c)
{
	if (c >= 'A')
		c++;
	return (c % 2 != 0);
}

void			ft_round_hex(t_prnf *pf, char *num, char type)
{
	int			n;
	char		drop;

	drop = num[pf->prec + 1] >= '8' ? 'f' - 32 * ft_isupper(type) : '0';
	if (pf->prec >= 0 && pf->prec < pf->n1)
	{
		n = pf->prec + 1;
		if (ft_isodd(num[n + 1]) || num[n] > '8')
			while (num[--n] == drop)
				--pf->n1;
		if (drop == 'f' - 32 * ft_isupper(type) && (ft_isodd(num[n + 2]) ||
				num[n + 1] > '8' || (num[n + 1] == '8' && num[n + 2] != '0')))
			++num[n];
		num[n] = num[n] == ':' ? 'a' - 32 * ft_isupper(type) : num[n];
		pf->n1 = pf->prec == 0 ? 1 : pf->n1;
	}
	ft_memcpy(pf->s, num, 1);
	ft_memcpy(pf->s + 1, ".", 1);
	ft_memcpy(pf->s + 2, &num[1], pf->n1 - 1);
	if (pf->prec != 0 && pf->n1 >= 1)
		pf->n1++;
	if ((pf->n1 - 2) > pf->prec && pf->prec > 0)
		pf->nz1 = pf->n1 - pf->prec;
	else if (pf->prec > 0)
		pf->nz1 = pf->prec - pf->n1 + 2;
}
