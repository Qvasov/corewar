/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 17:29:20 by ddarell           #+#    #+#             */
/*   Updated: 2019/05/06 18:12:09 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	t_list	*tmp;

	if (new == NULL)
		return ;
	if (alst == NULL)
		alst = &new;
	if (*alst == NULL)
		*alst = new;
	else
	{
		tmp = *alst;
		new->next = tmp;
		*alst = new;
	}
	return ;
}
