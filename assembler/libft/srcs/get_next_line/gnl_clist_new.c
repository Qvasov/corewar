/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_clist_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 21:13:55 by laleta            #+#    #+#             */
/*   Updated: 2019/09/04 21:13:59 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_lists	*ft_clist_new(t_clist *clist, void *data)
{
	t_lists	*tmp;

	if (!clist || !(tmp = (t_lists*)malloc(sizeof(*tmp))))
		return (NULL);
	tmp->data = data;
	tmp->next = clist->parent_node;
	if (!clist->parent_node)
	{
		clist->parent_node = tmp;
		clist->list = tmp;
	}
	++(clist->list_size);
	return (tmp);
}
