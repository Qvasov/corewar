/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_clist_find_prev.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 21:15:48 by laleta            #+#    #+#             */
/*   Updated: 2019/09/04 21:15:55 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_lists	*ft_clist_find_prev(t_lists *wall)
{
	t_lists	*list;

	if (!wall || !wall->next)
		return (NULL);
	list = wall->next;
	while (list->next != wall)
		list = list->next;
	return (list);
}
