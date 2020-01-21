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
#include <errno.h>

void	ft_error(int8_t id)
{
	write (2, "ERROR\n", 6);
	exit(id);
}

void	ft_perror()
{
	ft_printf("%s\n", strerror(errno));
	perror("corewar");
	exit (1);
}
