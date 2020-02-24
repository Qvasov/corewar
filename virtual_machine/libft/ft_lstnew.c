/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:41:38 by ddarell           #+#    #+#             */
/*   Updated: 2019/05/05 21:00:22 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	if ((list = (t_list*)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	list->content_size = (content == (void*)0) ? 0 : content_size;
	if (list->content_size != 0)
	{
		if (!(list->content = malloc(sizeof(void) * (list->content_size))))
		{
			free(list);
			return (NULL);
		}
		list->content = ft_memmove(list->content, content, list->content_size);
	}
	else
		list->content = NULL;
	list->next = NULL;
	return (list);
}
