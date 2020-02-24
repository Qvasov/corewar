/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mult_sum_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:57:14 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 16:20:48 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_rev_mult_array_num(char *buf, unsigned long long int num)
{
	unsigned long long int	carry;
	int						k;

	carry = 0;
	k = 0;
	while (*buf)
	{
		carry = (*buf - '0') * num + carry;
		*buf = (char)(carry % 10) + '0';
		carry /= 10;
		buf++;
	}
	while (carry > 0)
	{
		*buf = (char)(carry % 10) + '0';
		carry /= 10;
		buf++;
		k++;
	}
	*buf = 0;
	return (k);
}

int	ft_rev_sum_array_array(char *res, char *arr)
{
	int	i;
	int	f;

	i = 0;
	f = 0;
	while (res[i] && arr[i])
	{
		f = (int)(res[i] + arr[i] - 2 * '0' + f % 10);
		res[i] = (char)(f % 10 + '0');
		f /= 10;
		i++;
	}
	while (arr[i])
	{
		f = arr[i] - '0' + f % 10;
		res[i] = (char)(f % 10 + '0');
		f /= 10;
		i++;
	}
	if (f)
		res[i] = (char)(f % 10 + '0');
	res[i + (f > 0)] = 0;
	return (f);
}
