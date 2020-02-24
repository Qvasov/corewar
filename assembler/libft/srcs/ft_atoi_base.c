/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 17:53:13 by laleta            #+#    #+#             */
/*   Updated: 2019/04/11 00:31:54 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_base_err(const char *base)
{
	int			i;
	int			j;
	int			radix;

	i = 0;
	radix = ft_strlen(base);
	if (radix < 2)
		return (1);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-' || (base[i] < 32 || base[i] > 126))
			return (1);
		j = i + 1;
		while (base[j] && j < radix)
		{
			if (base[i] == base[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int		ft_str_err(const char *str, const char *base)
{
	int			i;
	int			j;
	int			radix;

	i = 0;
	radix = ft_strlen(base);
	if (ft_strlen(str) < 1)
		return (1);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ' || str[i] == '+'
			|| str[i] == '-')
		i++;
	while (str[i])
	{
		j = 0;
		while (base[j])
		{
			if (str[i] != base[j] && j == radix - 1)
				return (1);
			else
				break ;
			j++;
		}
		i++;
	}
	return (0);
}

int				ft_atoi_base(const char *str, const char *base)
{
	long int	nb;
	int			neg;
	int			i;
	int			j;

	if (ft_base_err(base) || ft_str_err(str, base))
		return (0);
	nb = 0;
	i = 0;
	neg = 1;
	while (str[i])
	{
		if (str[i] == '-')
			neg = -1;
		j = 0;
		while (base[j])
		{
			if (str[i] == base[j])
				nb = nb * ft_strlen(base) + j;
			j++;
		}
		i++;
	}
	return (neg * nb);
}
