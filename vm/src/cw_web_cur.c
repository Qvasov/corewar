/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_web_cur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 20:43:53 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/15 20:43:54 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		web_cur_parse(t_data *data, t_cur *cursor)
{
	int	num_player;

	num_player = cursor->reg[0] * -1;
	if (num_player > 0 && num_player <= data->vm.num_of_players)
	{
		--data->web.curs[num_player - 1][0];
		++data->web.curs[num_player - 1][cursor->op];
	}
}

void		web_cur_before_do(t_data *data, t_cur *cursor)
{
	data->web.arena[cursor->pc] -= 1000;
	data->web.change[cursor->pc] = data->web.arena[cursor->pc];
}

void		web_cur_after_do(t_data *data, t_cur *cursor)
{
	if (data->web.change[cursor->pc] == -1)
		data->web.change[cursor->pc] = data->web.arena[cursor->pc] + 1000;
	else
		data->web.change[cursor->pc] += 1000;
}
