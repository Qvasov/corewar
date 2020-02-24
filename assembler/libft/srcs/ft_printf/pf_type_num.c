/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_type_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 00:54:12 by laleta            #+#    #+#             */
/*   Updated: 2019/07/01 04:08:48 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_type_d_i(char type, char *buf, t_prnf *pf, va_list *ap)
{
	pf->nbr.i = pf->size == 'l' || pf->size == 'j' || pf->size == 'z' ||
					type == 'D' ? va_arg(*ap, int64_t) : va_arg(*ap, int32_t);
	if (type != 'D' && pf->size == 'h' && pf->size2 != 'h')
		pf->nbr.i = (int16_t)pf->nbr.i;
	if (type != 'D' && pf->size == 'h' && pf->size2 == 'h')
		pf->nbr.i = (char)pf->nbr.i;
	if (pf->nbr.i < 0)
		buf[pf->n0++] = '-';
	else if (pf->flags & F_PL)
		buf[pf->n0++] = '+';
	else if (pf->flags & F_SP)
		buf[pf->n0++] = ' ';
	pf->s = &buf[pf->n0];
	ft_itoa_base(pf, type);
}

void	ft_type_o_u_x(char type, char *buf, t_prnf *pf, va_list *ap)
{
	pf->nbr.i = pf->size == 'l' || pf->size == 'j' || pf->size == 'z' ||
				ft_isupper(type) ? va_arg(*ap, int64_t) : va_arg(*ap, int32_t);
	if (pf->size == 'h' && pf->size2 != 'h' && type != 'U' && type != 'O')
		pf->nbr.i = (uint16_t)pf->nbr.i;
	if (pf->size == 'h' && pf->size2 == 'h' && type != 'U' && type != 'O')
		pf->nbr.i = (unsigned char)pf->nbr.i;
	else if (pf->size == '\0' && type != 'U' && type != 'O')
		pf->nbr.i = (uint32_t)pf->nbr.i;
	if (pf->flags & F_PO && pf->nbr.i != 0)
	{
		buf[pf->n0++] = '0';
		if (type == 'x' || type == 'X' || type == 'b' || type == 'B')
			buf[pf->n0++] = type;
	}
	pf->s = &buf[pf->n0];
	ft_itoa_base(pf, type);
}

void	ft_type_e_f_g_a(char type, char *buf, t_prnf *pf, va_list *ap)
{
	pf->nbr.f = pf->size == 'L' ? va_arg(*ap, long double) :
															va_arg(*ap, double);
	if (((uint16_t *)&(pf->nbr.f))[4] & 0x8000)
		buf[pf->n0++] = '-';
	else if (pf->flags & F_PL)
		buf[pf->n0++] = '+';
	else if (pf->flags & F_SP)
		buf[pf->n0++] = ' ';
	if (type == 'a' || type == 'A')
	{
		buf[pf->n0++] = '0';
		buf[pf->n0++] = type == 'A' ? 'X' : 'x';
	}
	pf->s = &buf[pf->n0];
	ft_ftoa(pf, type);
}
