/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 19:07:35 by ddarell           #+#    #+#             */
/*   Updated: 2019/05/02 16:13:14 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intmin(char *num)
{
	num[0] = '-';
	num[1] = '2';
	return (0);
}

static int	ft_put_digit(char *num, int ord, int n)
{
	int del;

	del = 10;
	while (--ord && del < 1000000000)
	{
		del = del * 10;
	}
	if (del == 1000000000 && n >= 1000000000)
	{
		*num = ((n / 10) % del / (del / 10)) + '0';
		num++;
	}
	while (del >= 10)
	{
		*num = (n % del / (del / 10)) + '0';
		del = del / 10;
		num++;
	}
	*num = 0;
	return (0);
}

char		*ft_itoa(int n)
{
	char	*num;
	int		ord;
	int		i;

	ord = 1;
	i = n;
	while ((i = i / 10) != 0)
		ord++;
	ord = (n >= 0) ? ord : ord + 1;
	if (!(num = (char*)malloc(sizeof(char) * (ord + 1))))
		return (NULL);
	if (n == -2147483648)
	{
		ft_intmin(num);
		ft_put_digit(num + 2, 9, 147483648);
		return (num);
	}
	if (n < 0)
	{
		num[i++] = '-';
		n = -n;
		ord--;
	}
	ft_put_digit(num + i, ord, n);
	return (num);
}
