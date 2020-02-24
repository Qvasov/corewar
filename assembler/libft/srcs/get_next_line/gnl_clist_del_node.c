/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_clist_del_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 21:13:19 by laleta            #+#    #+#             */
/*   Updated: 2019/09/04 21:13:28 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_clist_del_node(t_clist *clist, t_lists **node, void (*del)(void**))
{
	t_lists	*prev;
	t_lists	*tmp;

	if (!node || !*node || !clist)
		return ;
	prev = ft_clist_find_prev(*node);
	tmp = (*node)->next;
	if (*node == clist->parent_node)
		clist->parent_node = tmp;
	if (del)
		del(&(*node)->data);
	free(*node);
	*node = NULL;
	--(clist->list_size);
	if (prev)
		prev->next = tmp;
	if (tmp == clist->parent_node)
		clist->list = tmp;
}
