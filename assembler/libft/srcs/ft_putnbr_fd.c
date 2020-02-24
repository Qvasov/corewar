/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:06:54 by laleta            #+#    #+#             */
/*   Updated: 2019/04/07 19:07:14 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putnbr_fd(int nb, int fd)
{
	char		num_arr[10];
	int			i;
	long int	num;

	num = nb;
	i = 0;
	if (num < 0)
	{
		num *= -1;
		ft_putchar_fd('-', fd);
	}
	while (num > 9)
	{
		num_arr[i++] = num % 10;
		num /= 10;
	}
	if (num <= 9)
		num_arr[i] = num;
	while (i >= 0)
		ft_putchar_fd(num_arr[i--] + '0', fd);
}
