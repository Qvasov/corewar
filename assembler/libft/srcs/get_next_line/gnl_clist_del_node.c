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

void	ft_clist_del_node(t_clist *clist, t_lists **node)
{
	t_lists	*prev;
	t_lists	*tmp;
	t_fileb	*file_data;

	if (!node || !*node || !clist)
		return ;
	prev = ft_clist_find_prev(*node);
	tmp = (*node)->next;
	if (*node == clist->parent_node)
		clist->parent_node = tmp;
	file_data = (*node)->data;
	ft_strdel(&file_data->buffer);
	ft_memdel(&(*node)->data);
	free(*node);
	*node = NULL;
	--(clist->list_size);
	if (prev)
		prev->next = tmp;
	if (tmp == clist->parent_node)
		clist->list = tmp;
}

int		ft_clist_free(t_clist *clist)
{
	t_fileb	*file_data;
	t_lists	*list;
	t_lists	*node;

	if (!clist)
		return (0);
	list = clist->list;
	while (list)
	{
		node = list->next;
		file_data = list->data;
		ft_strdel(&file_data->buffer);
		ft_memdel(&list->data);
		free(list);
		list = node;
	}
	return (0);
}
