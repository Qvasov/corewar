/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_clist_insert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 21:13:39 by laleta            #+#    #+#             */
/*   Updated: 2019/09/04 21:13:44 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_lists	*ft_clist_insert(t_clist *clist, t_lists *current, void *data)
{
	t_lists	*new;
	t_lists	*tmp;

	if (!clist || !current)
		return (NULL);
	if (!(new = ft_clist_new(clist, data)))
		return (NULL);
	if (current->next)
		tmp = current->next;
	else
		tmp = current;
	current->next = new;
	new->next = tmp;
	return (new);
}
