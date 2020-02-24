/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 02:14:09 by laleta            #+#    #+#             */
/*   Updated: 2019/07/01 05:09:56 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "pf_dragon4.h"

int32_t				ft_iszero(char *buf)
{
	while (*buf++)
		if (*buf != '0')
			return (0);
	return (1);
}

void static inline	ft_round(int16_t *sdig, int16_t *dig_cnt, char **pbuf,
															int16_t *exp_dig)
{
	const char	drop = *sdig < *dig_cnt && (*pbuf)[*sdig] >= '5' ? '9' : '0';
	int			n;

	n = *sdig;
	while ((*pbuf)[--n] == drop)
		--*sdig;
	if (drop == '9' && (*sdig >= 0 && ((*pbuf)[n] % 2 != 0 ||
		(*pbuf)[n + 1] > '5' || ((*pbuf)[n + 1] == '5' &&
												!ft_iszero(&(*pbuf)[n + 2])))))
		++((*pbuf)[n]);
	if (n < 0)
	{
		--(*pbuf);
		++*sdig;
		++(exp_dig[0]);
	}
	exp_dig[1] = *sdig;
}

void static inline	ft_ftoa_aux(t_prnf *pf, char type, char *pbuf, char *buf)
{
	t_bigint	bigints[5];
	int16_t		dig_cnt;
	int16_t		sdig;
	int16_t		exp;
	int16_t		exp_dig[2];

	dig_cnt = dragon4(&buf[1], bigints, &pf->nbr.f, (int*)&exp);
	buf[0] = '0';
	pbuf = &buf[1];
	while (*pbuf == '0')
	{
		--dig_cnt;
		--exp;
		++pbuf;
	}
	if (type == 'f' || type == 'F')
		sdig = pf->prec + exp + 1;
	else
		sdig = pf->prec + (type == 'e' || type == 'E' ? 1 : 0);
	if (dig_cnt < sdig)
		sdig = dig_cnt;
	exp_dig[0] = exp;
	if (sdig > 0)
		ft_round(&sdig, &dig_cnt, &pbuf, exp_dig);
	ft_gen_ftype(pf, type, pbuf, exp_dig);
}

void static inline	ft_put_inf_nan(t_prnf *pf, char type, int16_t inf_nan)
{
	if (ft_isupper(type))
		ft_memcpy(pf->s, inf_nan == NAN ? "NAN" : "INF", pf->n1 = 3);
	else
		ft_memcpy(pf->s, inf_nan == NAN ? "nan" : "inf", pf->n1 = 3);
	pf->n0 = inf_nan == NAN ? 0 : pf->n0;
}

void				ft_ftoa(t_prnf *pf, char type)
{
	char		buf[16386];
	char		*pbuf;
	int16_t		inf_nan;
	int16_t		exp_dig[2];

	pbuf = buf;
	if (pf->prec < 0 && type != 'a' && type != 'A')
		pf->prec = 6;
	else if (pf->prec == 0 && (type == 'g' || type == 'G'))
		pf->prec = 1;
	if ((inf_nan = ft_get_inf_nan(&pf->nbr.f)) > 0)
		return (ft_put_inf_nan(pf, type, inf_nan));
	else if (type == 'a' || type == 'A')
		return (ft_ftoa_hex(pf, type, 0));
	else if (inf_nan == 0)
	{
		exp_dig[0] = 0;
		exp_dig[1] = 0;
		ft_gen_ftype(pf, type, pbuf, exp_dig);
	}
	else
		ft_ftoa_aux(pf, type, pbuf, buf);
}
