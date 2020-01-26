/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 16:31:55 by ddarell           #+#    #+#             */
/*   Updated: 2019/05/02 16:54:58 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_put_digit(int ord, int n)
{
	int		del;
	char	c;

	del = 10;
	while (--ord && del < 1000000000)
	{
		del = del * 10;
	}
	if (del == 1000000000 && n >= 1000000000)
	{
		c = ((n / 10) % del / (del / 10)) + '0';
		write(1, &c, 1);
	}
	while (del >= 10)
	{
		c = (n % del / (del / 10)) + '0';
		del = del / 10;
		write(1, &c, 1);
	}
	return (0);
}

void		ft_putnbr(int n)
{
	int ord;
	int tmp;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	ord = 1;
	tmp = n;
	while ((tmp = tmp / 10) != 0)
		ord++;
	ft_put_digit(ord, n);
	return ;
}
