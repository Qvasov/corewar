/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 18:17:48 by ddarell           #+#    #+#             */
/*   Updated: 2019/05/08 15:24:43 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_deleting(void *content, size_t content_size)
{
	free(content);
	content_size = 0;
	return ;
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *tmp;
	t_list *map;

	map = NULL;
	tmp = NULL;
	if (f == NULL)
		return (NULL);
	while (lst)
	{
		tmp = (*f)(lst);
		if (!(tmp = ft_lstnew(tmp->content, tmp->content_size)))
		{
			ft_lstdel(&map, &ft_deleting);
			return (NULL);
		}
		ft_lstaddback(&map, tmp);
		lst = lst->next;
	}
	return (map);
}
