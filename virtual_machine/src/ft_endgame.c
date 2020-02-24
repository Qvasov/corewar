/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endgame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:17:58 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/28 17:17:59 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_endgame(t_data *data)
{
	if (data->web_flag)
	{
		ft_fprintf(data->web.fd, "];\nconst winner = \"%s\";\n",
				data->player[data->vm.last_player_id - 1].name);
		(close(data->web.fd) < 0) ? ft_perror(NULL) : 1;
		ft_web_free(data);
		system("open web/CoreWar.html");
	}
	if (data->nc_flag)
	{
		render(&data->vm, data->player);
		endwin();
	}
	if (data->web_flag == 0 && data->nc_flag == 0)
	{
		if (data->o_flag == 1)
			ft_bprintf(&data->fstr, "Contestant %hhd, \"%s\", has won !\n",
					data->vm.last_player_id,
					data->player[data->vm.last_player_id - 1].name);
		else
			ft_bprintf(&data->fstr, "Player %hhd, (%s), won\n",
					data->vm.last_player_id,
					data->player[data->vm.last_player_id - 1].name);
		ft_buf_print(&data->fstr);
	}
}
