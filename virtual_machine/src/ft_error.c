/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 19:48:38 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/21 19:48:40 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_error(char *str)
{
	ft_fprintf(2, "./corewar: %s\n", str);
	exit(1);
}

void	ft_perror(t_data *data)
{
	perror("corewar");
	if (data != NULL)
		ft_buf_print(&data->fstr);
	exit(1);
}
