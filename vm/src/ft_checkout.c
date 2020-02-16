/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkout.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 21:54:11 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/15 21:54:12 by dbennie          ###   ########.fr       */
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

void		ft_checkout(t_data *data)
{
	t_cur	*cursor;
	t_cur	*tmp;
	t_vm	*vm;

	vm = &data->vm;
	cursor = vm->cursor;
	while (cursor)
	{
		if ((vm->cycle + vm->cycle_from_start) - cursor->cycle_of_last_live >= vm->cycles_to_die || vm->cycles_to_die <= 0)
		{
			(data->web_flag) ? data->web.arena[cursor->pc] -= 1000 : 1;
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

		if (data->v_flag.bit1)
			ft_printf("Cycle to die is now %d\n", vm->cycles_to_die);

		vm->number_of_check = 0;
	}
	vm->number_of_live = 0;
	vm->cycle_from_start += vm->cycle;
	vm->cycle = 0;
}

