/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 02:27:20 by laleta            #+#    #+#             */
/*   Updated: 2019/06/24 05:45:15 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_gen_ftype(t_prnf *pf, char type, char *buf, int16_t *exp_dig)
{
	int32_t	n;

	if (exp_dig[1] <= 0)
	{
		exp_dig[1] = 1;
		buf = "0";
	}
	if (type == 'f' || type == 'F' || ((type == 'g' || type == 'G')
								&& exp_dig[0] >= -4 && exp_dig[0] < pf->prec))
		ft_gen_f(pf, type, buf, exp_dig);
	else
		ft_gen_e(pf, type, buf, exp_dig);
	if ((pf->flags & (F_MI | F_ZE)) == F_ZE)
	{
		n = pf->n0 + pf->n1 + pf->nz1 + pf->n2 + pf->nz2;
		if (n < pf->width)
			pf->nz0 = pf->width - n;
	}
}
