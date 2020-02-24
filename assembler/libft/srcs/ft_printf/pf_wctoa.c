/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_wctoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 04:24:38 by laleta            #+#    #+#             */
/*   Updated: 2019/06/24 02:02:49 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				ft_conv_char(uint32_t wc, char *conv)
{
	if (wc <= 0x7F)
		conv[0] = wc;
	else if (wc <= 0x7FF)
	{
		conv[0] = ((wc >> 6) + 0xC0);
		conv[1] = ((wc & 0x3F) + 0x80);
	}
	else if (wc <= 0xFFFF)
	{
		conv[0] = ((wc >> 12) + 0xE0);
		conv[1] = (((wc >> 6) & 0x3F) + 0x80);
		conv[2] = ((wc & 0x3F) + 0x80);
	}
	else if (wc <= 0x10FFFF)
	{
		conv[0] = ((wc >> 18) + 0xF0);
		conv[1] = (((wc >> 12) & 0x3F) + 0x80);
		conv[2] = (((wc >> 6) & 0x3F) + 0x80);
		conv[3] = ((wc & 0x3F) + 0x80);
	}
}

int32_t				ft_wcharlen(uint32_t wc)
{
	if (wc <= 0x7F)
		return (1);
	else if (wc <= 0x7FF)
		return (2);
	else if (wc <= 0xFFFF)
		return (3);
	else if (wc <= 0x10FFFF)
		return (4);
	return (0);
}

static inline void	ft_wctoa_c(t_prnf *pf, uint32_t *wc, char *conv)
{
	ft_conv_char(*wc, conv);
	pf->n1 = ft_wcharlen(*wc);
	ft_memcpy(pf->s, conv, pf->n1);
}

void				ft_wctoa(t_prnf *pf, uint32_t *wc, char type)
{
	char			conv[4];
	int16_t			wc_len;
	int16_t			l;

	l = 0;
	if (type == 'C' || type == 'c')
		ft_wctoa_c(pf, wc, conv);
	else
	{
		while (*wc != L'\0')
		{
			ft_conv_char(*wc, conv);
			wc_len = ft_wcharlen(*wc);
			if (pf->prec >= l + wc_len || pf->prec < 0)
			{
				ft_memcpy(pf->s + l, conv, wc_len);
				l += wc_len;
			}
			else
				break ;
			++wc;
		}
		pf->n1 = l;
	}
}
