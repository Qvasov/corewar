/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_cursor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 19:03:18 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/27 19:03:19 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_cur	*ft_copy_cursor(t_vm *vm, t_cur *cursor)
{
	t_cur	*cur;
	int8_t	i;

	i = -1;
	!(cur = (t_cur *)malloc(sizeof(t_cur))) ? ft_perror(NULL) : 0;
	cur->id = ++vm->cursor_id;
	cur->carry = cursor->carry;
	cur->op_code = 0;
	cur->cycle_of_last_live = cursor->cycle_of_last_live;
	cur->cycles_to_do_op = 0;
	cur->byte_to_next_op = 0;
//	cur->reg = (int *)malloc(sizeof(int) * 12);//
	while (++i < REG_NUMBER)
		cur->reg[i] = cursor->reg[i];
	cur->prev = NULL;
	cur->next = vm->cursor; //куда располагается в списке
	(vm->cursor) ? vm->cursor->prev = cur : 0;
	vm->cursor = cur;
	return (cur);
}
