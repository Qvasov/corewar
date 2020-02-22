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

static void	check_to_del(t_data *data, t_vm *vm, t_cur *cursor)
{
	t_cur	*tmp;

	while (cursor)
	{
		if ((vm->cycle + vm->cycle_from_start) - cursor->cycle_of_last_live >=
			vm->cycles_to_die || vm->cycles_to_die <= 0)
		{
			(data->web_flag) ? data->web.arena[cursor->pc] -= 1000 : 1;
			(ft_bit_check(data->v_flag, 3)) ? flag_v8(data, cursor) : 0;
			tmp = cursor;
			cursor = cursor->next;
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			else
				vm->cursor = tmp->next;
			if (tmp->next)
				tmp->next->prev = (tmp->prev) ? tmp->prev : NULL;
			free(tmp);
		}
		else
			cursor = cursor->next;
	}
}

void		ft_checkout(t_data *data)
{
	t_cur	*cursor;
	t_vm	*vm;

	vm = &data->vm;
	cursor = vm->cursor;
	check_to_del(data, vm, cursor);
	++vm->number_of_check;
	if (vm->number_of_live >= NBR_LIVE || vm->number_of_check >= MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		if (ft_bit_check(data->v_flag, 1))
			flag_v2_ctd(data);
		vm->number_of_check = 0;
	}
	vm->number_of_live = 0;
	vm->cycle_from_start += vm->cycle;
	vm->cycle = 0;
}
