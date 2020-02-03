/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 18:29:26 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/30 18:29:27 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	del_cursor(t_vm *vm, t_cur *cursor)
{
	if (cursor->prev)
		cursor->prev->next = cursor->next;
	else
		vm->cursor = cursor->next;
	if (cursor->next)
		cursor->next->prev = (cursor->prev) ? cursor->prev : NULL;
	free(cursor);
}

void		ft_check(t_vm *vm)
{
	t_cur	*cursor;
	t_cur	*tmp;
	int sum = vm->cycle + vm->cycle_from_start;


	cursor = vm->cursor;
	while (cursor)
	{
		if ((vm->cycle + vm->cycle_from_start) - cursor->cycle_of_last_live >= vm->cycles_to_die || vm->cycles_to_die <= 0)
		{
			tmp = cursor;
			cursor = cursor->next;
			del_cursor(vm, tmp);
		}
		else
			cursor = cursor->next;
	}
	++vm->number_of_check;
	if (vm->number_of_live >= NBR_LIVE || vm->number_of_check >= MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		ft_printf("Cycle to die is now %d\n", vm->cycles_to_die);
		vm->number_of_check = 0;
	}
	vm->number_of_live = 0;
	vm->cycle_from_start += vm->cycle;
	vm->cycle = 0;
}

