/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:11:31 by laleta            #+#    #+#             */
/*   Updated: 2019/04/10 14:05:10 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		check_max(long int nb, const char c, int neg)
{
	long int	max;

	max = -1;
	max = (unsigned long)max >> 1;
	if (nb > max / 10)
	{
		if (neg == 1)
			return (2);
		else
			return (1);
	}
	if (nb * 10 > max - c + '0')
	{
		if (neg == 1)
			return (2);
		else
			return (1);
	}
	return (-1);
}

int				ft_atoi(const char *str)
{
	long int	nb;
	int			neg;
	int			i;
	int			max;

	nb = 0;
	i = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i + 1])
	{
		if (str[i] == '-' && str[i + 1] >= '0' && str[i + 1] <= '9')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((max = check_max(nb, str[i], neg)) != -1)
			return ((max == 1) ? 0 : -1);
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (neg * nb);
}
