/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_flag_v1_v2_v8_v16.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 21:33:28 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/24 21:33:29 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	flag_v1(t_data *data, int num_of_player)
{
	ft_bprintf(&data->fstr, "Player %d (%s) is said to be alive\n",
			num_of_player, data->player[num_of_player - 1].name);
}

void	flag_v2_c(t_data *data)
{
	ft_bprintf(&data->fstr, "It is now cycle %d\n",
			data->vm.cycle_from_start + data->vm.cycle);
}

void	flag_v2_ctd(t_data *data)
{
	ft_bprintf(&data->fstr, "Cycle to die is now %d\n", data->vm.cycles_to_die);
}

void	flag_v8(t_data *data, t_cur *cursor)
{
	ft_bprintf(&data->fstr,
			"Process %llu hasn't lived for %d cycles (CTD %lld)\n",
			cursor->id, data->vm.cycle_from_start + data->vm.cycle -
			cursor->cycle_of_last_live, data->vm.cycles_to_die);
}

void	flag_v16(t_data *data, t_cur *cursor)
{
	int	i;

	i = -1;
	if (data->o_flag)
		ft_bprintf(&data->fstr, "ADV %d (0x%.4x -> 0x%.4x) ",
				cursor->byte_to_next_op,
				cursor->pc, cursor->pc + cursor->byte_to_next_op);
	else
		ft_bprintf(&data->fstr, "ADV %d (0x%.4x -> 0x%.4x) ",
				cursor->byte_to_next_op,
				cursor->pc, (cursor->pc + cursor->byte_to_next_op) % MEM_SIZE);
	while (++i < cursor->byte_to_next_op)
		ft_bprintf(&data->fstr, "%.2hhx ",
				data->vm.arena[(cursor->pc + i) % MEM_SIZE]);
	ft_bprintf(&data->fstr, "\n");
}
