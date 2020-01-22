/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 19:48:48 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/21 19:48:50 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vm.h"

void	ft_init_arena(t_vm *vm, t_players *players)
{
	int8_t	i;
	int16_t	delta;

	delta = 0;
	i = -1;
	while (++i < players->number_of_players)
	{
		ft_memcpy(&vm->arena[delta], players->player[i].exec_code, players->player[i].exec_size);
		delta += ((MEM_SIZE) / players->number_of_players);
	}
	vm->cursor = NULL;
	vm->cursor_id = 0;
	vm->cycles_from_start = 0;
	vm->cycles_to_die = 1536;
	vm->last_player_id = 0;
	vm->number_of_live_operations = 0;
}
