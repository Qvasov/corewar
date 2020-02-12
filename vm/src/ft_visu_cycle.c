/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_visu_cycle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 17:40:39 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/12 17:40:40 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_visu_cycle(t_data *data)
{
	int	i;
	int n;

	ft_fprintf(data->visu.fd, "[[");
	data->visu.f = 0;
	n = -1;
	while (++n < data->vm.num_of_players)
	{
		i = -1;
		while (++i < 17)
		{
			if (data->visu.curs[n][i] > 0)
			{
				data->visu.f ? ft_fprintf(data->visu.fd, ", ") : 1;
				ft_fprintf(data->visu.fd, "%d, %d, %d", data->visu.curs[n][i] - 1, i, n + 1);
				data->visu.f = 1;
			}
			if (n + 1 == data->vm.num_of_players && i + 1 == 17)
				ft_fprintf(data->visu.fd, "], [");
		}
	}

	data->visu.f = 0;
	i = -1;
	while(++i < MEM_SIZE)
	{
		if (data->visu.change[i] != 0)
		{
			data->visu.f ? ft_fprintf(data->visu.fd, ", ", i, data->visu.change[i], data->vm.cycles_to_die) : 1;
			data->visu.arena[i] += data->visu.change[i]; //tut
			data->visu.change[i] = 0;
			ft_fprintf(data->visu.fd, "%u, %u", i, data->visu.arena[i]);
			data->visu.f = 1;
		}
		if (i + 1 == MEM_SIZE)
			ft_fprintf(data->visu.fd, "], [%d]], ", data->vm.cycles_to_die);
	}
//	ft_bzero(data->visu.change, 4 * MEM_SIZE);
}
