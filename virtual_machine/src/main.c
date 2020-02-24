/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 16:02:31 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/21 19:49:24 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	analysis_flags(t_data *data)
{
	if (data->nc_flag || data->web_flag)
	{
		if (data->nc_flag)
			data->web_flag = 0;
		data->v_flag = 0;
		data->l_flag = 1;
		data->vm.nbr_cycles = -1;
	}
}

static void	init_flags(t_data *data)
{
	data->v_flag = 0;
	data->web_flag = 0;
	data->nc_flag = 0;
	data->o_flag = 0;
	data->l_flag = 0;
}

static void	init_data(t_data *data)
{
	int i;

	i = -1;
	ft_bzero(data->vm.arena, MEM_SIZE);
	data->vm.cursor = NULL;
	data->vm.cursor_id = 0;
	data->vm.nbr_cycles = -1;
	data->vm.cycle = 0;
	data->vm.cycle_from_start = 0;
	data->vm.cycles_to_die = 1536;
	data->vm.number_of_live = 0;
	data->vm.number_of_check = 0;
	data->vm.min_player_id = 1;
	data->vm.num_of_players = 0;
	data->size[0] = 0;
	data->size[REG_CODE] = 1;
	data->size[DIR_CODE] = DIR_SIZE;
	data->size[IND_CODE] = IND_SIZE;
	while (++i <= MAX_PLAYERS)
		data->player[i].path = NULL;
	init_flags(data);
	ft_init_fstr(&data->fstr);
}

int			main(int ac, char **av)
{
	t_data	data;

	if (ac <= 1)
		ft_usage();
	init_data(&data);
	ft_parse(ac, av, &data);
	ft_read_valid_players(&data.vm, data.player,
		PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE + 4 * 4);
	analysis_flags(&data);
	ft_introducing(&data);
	ft_battle(&data);
	ft_endgame(&data);
	ft_free(&data);
	return (0);
}
