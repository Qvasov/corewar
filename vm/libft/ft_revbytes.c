/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revbytes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:20:19 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/20 19:20:21 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			revbytes_int(int num)
{
	unsigned char	byte;
	int				tmp;
	size_t			i;

	tmp = 0;
	i = sizeof(int);
	while (i--)
	{
		byte = (char)num;
		tmp = tmp << 8;
		tmp += byte;
		num = num >> 8;
	}
	return (tmp);
}

long long	revbytes_long(long long num)
{
	unsigned char	byte;
	long long		tmp;
	size_t			i;

	tmp = 0;
	i = sizeof(long long);
	while (i--)
	{
		byte = (char)num;
		tmp = tmp << 8;
		tmp += byte;
		num = num >> 8;
	}
	return (tmp);
}
