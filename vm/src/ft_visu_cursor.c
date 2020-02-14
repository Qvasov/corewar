/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_visu_cursor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 17:16:09 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/12 17:16:10 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_visu_cur_parse(t_data *data, t_cur *cursor)
{
	int	num_player;

	num_player = cursor->reg[0] * -1;
	if (num_player > 0 && num_player <= data->vm.num_of_players)
	{
		--data->visu.curs[num_player - 1][0];
		++data->visu.curs[num_player - 1][cursor->op_code];
	}
}

void		ft_visu_cur_before_do(t_data *data, t_cur *cursor)
{
	int	num_player;

	num_player = cursor->reg[0] * -1;
	if (num_player > 0 && num_player <= data->vm.num_of_players)
		data->visu.arena[cursor->pc] = data->visu.arena[cursor->pc] - 1000;
}

void		ft_visu_cur_after_do(t_data *data, t_cur *cursor)
{
	int	num_player;

	num_player = cursor->reg[0] * -1;
	if (num_player > 0 && num_player <= data->vm.num_of_players)
		data->visu.change[cursor->pc] = data->visu.arena[cursor->pc] + 1000;
}
