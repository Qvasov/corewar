/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 23:43:43 by laleta            #+#    #+#             */
/*   Updated: 2019/04/01 23:43:52 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int	div;
	int res;

	div = nb;
	res = nb;
	if (nb <= 0)
		return (0);
	while (1)
	{
		div = (nb / div + div) / 2;
		if (res > div)
			res = div;
		else if (res * res == nb)
			return (res);
		else
			return (0);
	}
}
