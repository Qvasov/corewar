/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_buf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:45:41 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/25 15:45:42 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_buf(char *buf, size_t *i, size_t buff_size, int num)
{
	if (num / 10)
		ft_putnbr_buf(buf, i, buff_size, num / 10);
	ft_putchar_buf(buf, i, buff_size, num % 10 + '0');
}
