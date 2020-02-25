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

t_cur	*ft_copy_cursor(t_data *data, t_cur *cursor)
{
	t_cur	*cur;
	int8_t	i;

	i = -1;
	if (!(cur = (t_cur *)malloc(sizeof(t_cur))))
	{
		(data->nc_flag) ? visu_init() : 0;
		ft_perror(NULL);
	}
	cur->id = ++data->vm.cursor_id;
	cur->carry = cursor->carry;
	cur->op = 0;
	cur->cycle_of_last_live = cursor->cycle_of_last_live;
	cur->cycles_to_do_op = 0;
	cur->byte_to_next_op = 0;
	while (++i < REG_NUMBER)
		cur->reg[i] = cursor->reg[i];
	cur->prev = NULL;
	cur->next = data->vm.cursor;
	(data->vm.cursor) ? data->vm.cursor->prev = cur : 0;
	data->vm.cursor = cur;
	return (cur);
}
