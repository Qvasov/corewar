/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_web_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 20:44:04 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/15 20:44:05 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	memory_changes(t_data *data)
{
	int	i;

	data->web.f = 0;
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (data->web.change[i] > -1)
		{
			data->web.f ? ft_fprintf(data->web.fd, ", ") : 1;
			data->web.arena[i] = data->web.change[i];
			data->web.change[i] = -1;
			ft_fprintf(data->web.fd, "%u, %u", i, data->web.arena[i]);
			data->web.f = 1;
		}
		if (i + 1 == MEM_SIZE)
			ft_fprintf(data->web.fd, "], [%d]], ", data->vm.cycles_to_die);
	}
}

void		web_cycle(t_data *data)
{
	int	i;
	int n;

	ft_fprintf(data->web.fd, "[[");
	data->web.f = 0;
	n = -1;
	while (++n < data->vm.num_of_players)
	{
		i = -1;
		while (++i < 17)
		{
			if (data->web.curs[n][i] > 0)
			{
				data->web.f ? ft_fprintf(data->web.fd, ", ") : 1;
				ft_fprintf(data->web.fd, "%d, %d, %d",
						data->web.curs[n][i] - 1, i, n + 1);
				data->web.f = 1;
			}
			if (n + 1 == data->vm.num_of_players && i + 1 == 17)
				ft_fprintf(data->web.fd, "], [");
		}
	}
	memory_changes(data);
}
