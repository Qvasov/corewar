/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_introducing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:06:51 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/23 16:06:52 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_introducing(t_data *data)
{
	int8_t	i;

	if (data->web_flag == 0 && data->nc_flag == 0)
	{
		i = -1;
		ft_bprintf(&data->fstr, "Introducing contestants...\n");
		while (++i < data->vm.num_of_players)
		{
			ft_bprintf(&data->fstr,
					"* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
					data->player[i].id, data->player[i].exec_size,
					data->player[i].name, data->player[i].comment);
		}
	}
	data->vm.last_player_id = data->vm.num_of_players;
}
