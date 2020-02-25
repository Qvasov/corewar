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

void	ft_init_cursors(t_vm *vm, t_champ *player)
{
	t_cur	*cur;
	int16_t	delta;
	int8_t	i;

	delta = 0;
	i = -1;
	while (++i < vm->num_of_players)
	{
		!(cur = (t_cur *)malloc(sizeof(t_cur))) ? ft_perror(NULL) : 0;
		cur->id = ++vm->cursor_id;
		cur->carry = 0;
		cur->op = 0;
		cur->cycle_of_last_live = 0;
		cur->cycles_to_do_op = 0;
		cur->pc = delta;
		cur->byte_to_next_op = 0;
		cur->reg[0] = player[i].id * -1;
		ft_bzero(&cur->reg[1], 60);
		cur->prev = NULL;
		cur->next = vm->cursor;
		(vm->cursor) ? vm->cursor->prev = cur : 0;
		vm->cursor = cur;
		delta += ((MEM_SIZE) / vm->num_of_players);
	}
}
