/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:00:51 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/09 17:00:52 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_free(t_data *data)
{
	t_cur	*cur;

	cur = data->vm.cursor;
	while (cur)
	{
		data->vm.cursor = data->vm.cursor->next;
		free(cur);
		cur = data->vm.cursor;
	}
}
