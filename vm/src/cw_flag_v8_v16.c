/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_flag_v.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:20:07 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/19 21:20:10 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	flag_v8(t_data *data, t_cur *cursor)
{
	ft_printf("Process %llu hasn't lived for %d cycles (CTD %lld)\n",
			  cursor->id,
			  data->vm.cycle_from_start + data->vm.cycle - cursor->cycle_of_last_live,
			  data->vm.cycles_to_die);
}

void	flag_v16(t_vm *vm, t_cur *cursor)
{
	int	i;

	ft_printf("ADV %d (0x%.4x -> 0x%.4x) ",
			  cursor->byte_to_next_op,
			  cursor->pc,
			  (cursor->pc + cursor->byte_to_next_op)/* % MEM_SIZE*/);
	i = -1;
	while (++i < cursor->byte_to_next_op)
		ft_printf("%.2hhx ", vm->arena[(cursor->pc + i) % MEM_SIZE]);
	ft_printf("\n");
}
