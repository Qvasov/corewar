/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_cursors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 21:34:30 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/22 21:34:33 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			ft_init_cursors(t_vm *vm, t_players *players)
{
	t_cursor	*cursor;
	int16_t		delta;
	int8_t		i;

	delta = 0;
	i = -1;
	while (++i < players->number_of_players)
	{
		!(cursor = (t_cursor *)malloc(sizeof(t_cursor))) ? ft_perror() : 0;
		cursor->id = ++vm->cursor_id;
		cursor->carry = 0;
		cursor->op_code = 0;
		cursor->cycle_of_last_live = 0;
		cursor->cycles_to_do_op = 0;
		cursor->position = delta;
		cursor->byte_step = vm->arena[delta + 1];
		cursor->reg[0] = players->player[i].id;
		ft_bzero(&cursor->reg[1], 60);
		cursor->next = vm->cursor;
		vm->cursor = cursor;
		delta += ((MEM_SIZE) / players->number_of_players);
	}
}
