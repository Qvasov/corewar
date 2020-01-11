/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 16:02:31 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/11 16:02:36 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	init_paths(t_path *player_paths)
{
	int i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		player_paths->flag_n[i] = 0;
		player_paths->path[i] = NULL;
	}
}

int main(int ac, char **av)
{
	t_path	player_paths;
	int		nbr_cycles;

	nbr_cycles = 0; //хз сколько по умолчанию (если -dump не прописан)
	(ac <= 1) ? ft_cw_usage() : 0;
	init_paths(&player_paths);
	ft_cw_args(ac, av, &player_paths, &nbr_cycles);
	ft_cw_read(player_paths);
//	ft_valid();
//	ft_arena();
	return (0);
}

//запись по индексу которые я получаю из -n, остальные заполняются по порядку.
