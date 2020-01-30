/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_buf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 19:18:31 by dbennie           #+#    #+#             */
/*   Updated: 2019/12/05 19:18:32 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_buf(char *buf, size_t *i, size_t buff_size, int num)
{
	if (num / 10)
		ft_putnbr_buf(buf, i, buff_size, num / 10);
	ft_putchar_buf(buf, i, buff_size, num % 10 + '0');
}
