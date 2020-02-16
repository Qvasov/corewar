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
	ft_printf("Contestant %hhd, \"%s\", has won !\n",
			data->vm.last_player_id, data->player[data->vm.last_player_id - 1].name);
	if (data->web_flag)
		ft_fprintf(data->web.fd, "];\nconst winner = \"%s\";\n", data->player[data->vm.last_player_id - 1].name);
	if (data->n_flag)
		endwin();
}
