/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_digit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:56:58 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/26 14:59:42 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_put_digit_dec(char *dig, unsigned int a, int size)
{
	int i;

	i = size;
	while (a || i == size)
	{
		--i;
		*(dig + i) = (char)(a % 10) + '0';
		a /= 10;
	}
	return (size - i);
}

int	ft_put_digit_oct(char *dig, unsigned int a, int size)
{
	int i;

	i = size;
	while (a || i == size)
	{
		--i;
		*(dig + i) = (char)((a & 7) + '0');
		a = a >> 3;
	}
	return (size - i);
}

int	ft_put_digit_hex(char *dig, unsigned int a, int size, char *base)
{
	int i;

	i = size;
	while (a || i == size)
	{
		--i;
		*(dig + i) = *(base + (a & 15));
		a = a >> 4;
	}
	return (size - i);
}

int	ft_put_digit_hex_ll(char *dig, unsigned long long int a,
						int size, char *base)
{
	int i;

	i = size;
	while (a || i == size)
	{
		--i;
		*(dig + i) = *(base + (a & 15));
		a = a >> 4;
	}
	return (size - i);
}

int	ft_put_digit_bin(char *dig, unsigned int a, int size)
{
	int i;

	i = size;
	while (a || i == size)
	{
		--i;
		*(dig + i) = (char)((a & 1) + '0');
		a = a >> 1;
	}
	return (size - i);
}
