/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_introducing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:06:51 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/23 16:06:52 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_introducing(t_data *data)
{
	int8_t	i;

	ft_printf("Introducing contestants...\n");
	i = -1;
	while (++i < data->vm.num_of_players)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				  data->player[i]->id, data->player[i]->exec_size,
				  data->player[i]->name, data->player[i]->comment);
	}
}
