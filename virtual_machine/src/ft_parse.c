/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 21:02:21 by ddarell           #+#    #+#             */
/*   Updated: 2020/01/29 21:04:37 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	merge_champ_tabs(t_champ *player, char **tmp_champ,
		int num_of_champs)
{
	int i;

	i = 0;
	while (*tmp_champ)
	{
		while (player[i].path)
			i++;
		player[i].path = *tmp_champ;
		i++;
		tmp_champ++;
	}
	while (player[i].path)
		i++;
	if (i != num_of_champs)
		ft_error("-n - number is bigger than number of champs");
}

static void	detect_champ(char **av, t_data *data, char **tmp_champ)
{
	int check;

	data->vm.num_of_players += 1;
	if (data->vm.num_of_players > MAX_PLAYERS)
		ft_error("too much players");
	check = ft_strlen(*av);
	if (check > 4 && ft_strcmp(*av + check - 4, ".cor") == 0)
		*tmp_champ = *av;
	else
		ft_error("champion name error");
}

static int	detect_flag(int ac, char **av, t_data *data, int r)
{
	if (ft_strcmp(*av, "-dump") == 0)
		(ac >= 2 && (r = 2)) ? ft_check_dump(av, &data->vm)
		: ft_error("-dump - no argument");
	else if (ft_strcmp(*av, "-n") == 0)
		(ac >= 3 && (r = 3)) ? ft_check_num_player(av, data)
		: ft_error("-n - no enough arguments");
	else if (ft_strcmp(*av, "-v") == 0)
		(ac >= 2 && (r = 2)) ? ft_check_v(av, data)
		: ft_error("-v - no argument");
	else if (ft_strcmp(*av, "-w") == 0)
		(ac >= 1 && (r = 1)) ?
		data->web_flag = 1 : ft_error("-w - error");
	else if (ft_strcmp(*av, "-nc") == 0)
		(ac >= 1 && (r = 1)) ?
		data->nc_flag = 1 : ft_error("-nc - error");
	else if (ft_strcmp(*av, "-o") == 0)
		(ac >= 1 && (r = 1)) ?
		data->o_flag = 1 : ft_error("-o - error");
	else if (ft_strcmp(*av, "-l") == 0)
		(ac >= 1 && (r = 1)) ?
		data->l_flag = 1 : ft_error("-l - error");
	else if (r == 0)
		ft_usage();
	return (r);
}

static void	parse_input(int ac, char **av, t_data *data, char **tmp_champ)
{
	int		jump;

	while (ac > 0)
	{
		if (**av == '-')
		{
			jump = detect_flag(ac, av, data, 0);
			ac -= jump;
			av += jump;
		}
		else
		{
			detect_champ(av, data, tmp_champ);
			av++;
			ac--;
			tmp_champ++;
		}
	}
}

void		ft_parse(int ac, char **av, t_data *data)
{
	char	*tmp_champ[MAX_PLAYERS + 1];
	int		i;

	i = -1;
	av++;
	ac--;
	while (++i <= MAX_PLAYERS)
		tmp_champ[i] = NULL;
	parse_input(ac, av, data, tmp_champ);
	(data->vm.num_of_players <= 0) ? ft_error("no champions found") : 1;
	merge_champ_tabs(data->player, tmp_champ, data->vm.num_of_players);
}
