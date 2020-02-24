/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 01:28:59 by laleta            #+#    #+#             */
/*   Updated: 2019/07/01 00:30:15 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "pf_types.h"

static char g_l[] = "0123456789abcdef";
static char g_u[] = "0123456789ABCDEF";

static void	ft_itoa_base_aux(t_prnf *pf, char type, int32_t base, uint64_t num)
{
	t_ldiv_t	qr;
	char		*digs;
	char		num_arr[64];
	int32_t		i;

	i = sizeof(num_arr);
	digs = type == 'X' ? g_u : g_l;
	if (num != 0 || (int)pf->prec != 0 || ((type == 'o' || type == 'O')
														&& (pf->flags & F_PO)))
		num_arr[--i] = digs[num % base];
	pf->nbr.i = num / base;
	while (pf->nbr.i > 0 && i > 0)
	{
		qr = ft_ldiv(pf->nbr.i, base);
		pf->nbr.i = qr.quot;
		num_arr[--i] = digs[qr.rem];
	}
	pf->n1 = sizeof(num_arr) - i;
	ft_memcpy(pf->s, &num_arr[i], pf->n1);
	if (pf->n1 < (int)pf->prec)
		pf->nz0 = (int)pf->prec - pf->n1;
}

void		ft_itoa_base(t_prnf *pf, char type)
{
	int32_t		base;
	int32_t		i;
	uint64_t	num;

	if (type == 'o' || type == 'O')
		base = 8;
	else if (type == 'b' || type == 'B')
		base = 2;
	else
		base = type != 'x' && type != 'X' ? 10 : 16;
	num = pf->nbr.i;
	if ((type == 'd' || type == 'D' || type == 'i') && pf->nbr.i < 0)
		num = -num;
	ft_itoa_base_aux(pf, type, base, num);
	if ((type == 'o' || type == 'O') && (pf->flags & F_PO) && (int)pf->prec > 0
																	&& num > 0)
	{
		--pf->nz0;
		if (pf->n1 >= (int)pf->prec)
			--pf->width;
	}
	if ((int)pf->prec < 0 && (pf->flags & (F_MI | F_ZE)) == F_ZE &&
		(i = pf->width - pf->n0 - pf->nz0 - pf->n1) > 0)
		pf->nz0 += i;
}

void		ft_type_r(char type, t_prnf *pf, int32_t i, int32_t j)
{
	uint32_t	cnt;
	char		*tm;

	cnt = 0;
	while (pf->s[i++])
		if (pf->s[i] < 32 && pf->s[i] >= 0)
			cnt++;
	tm = (char *)malloc(sizeof(char) * (ft_strlen(pf->s) + cnt * 3) + 1);
	i = -1;
	while (pf->s[++i])
	{
		if (pf->s[i] >= 0 && pf->s[i] < 32)
		{
			tm[j++] = '\\';
			tm[j++] = type == 'r' ? 'x' : 'X';
			tm[j++] = type == 'r' ? g_l[(pf->s[i]) / 16] : g_u[(pf->s[i]) / 16];
			tm[j++] = type == 'r' ? g_l[(pf->s[i]) % 16] : g_u[(pf->s[i]) % 16];
		}
		else
			tm[j++] = pf->s[i];
	}
	tm[j] = '\0';
	pf->s = tm;
	free(tm);
}

static void	ft_ftoa_hex_aux(t_prnf *pf)
{
	int32_t	n;

	if ((pf->flags & (F_MI | F_ZE)) == F_ZE)
	{
		n = pf->n0 + pf->n1 + pf->nz1 + pf->n2 + pf->nz2;
		if (n < pf->width)
			pf->nz0 = pf->width - n;
	}
}

void		ft_ftoa_hex(t_prnf *pf, char type, int16_t i)
{
	char		*digs;
	char		num_arr[17];
	uint64_t	mantis;
	int32_t		exp;
	int16_t		d;

	digs = type == 'A' ? g_u : g_l;
	ft_get_exp_mant(&pf->nbr.f, &exp, &mantis);
	i = sizeof(num_arr);
	while (--i >= 1)
	{
		d = (mantis & 0xF);
		mantis >>= 4;
		num_arr[i] = digs[d];
	}
	num_arr[i] = '1';
	i = sizeof(num_arr);
	num_arr[i] = '\0';
	while (num_arr[--i] == '0')
		;
	pf->n1 = i + 1;
	pf->n1 = pf->prec >= 0 && pf->prec < pf->n1 ? pf->prec + 1 : pf->n1;
	ft_round_hex(pf, num_arr, type);
	ft_put_exp(pf, type, num_arr, (int16_t)exp);
	ft_ftoa_hex_aux(pf);
}
