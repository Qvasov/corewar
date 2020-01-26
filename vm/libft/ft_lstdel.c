/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 21:21:04 by ddarell           #+#    #+#             */
/*   Updated: 2019/05/06 18:09:03 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*prev;

	if (alst == NULL || *alst == NULL || del == NULL)
		return ;
	while (*alst)
	{
		prev = *alst;
		*alst = (*alst)->next;
		(*del)((prev->content), (prev->content_size));
		prev->content = NULL;
		free(prev);
		prev = NULL;
	}
	return ;
}
