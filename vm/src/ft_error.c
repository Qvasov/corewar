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
//#include <errno.h>

void	ft_error(char *str)
{
	ft_printf("./corewar: %s\n", str); //ft_fprintf
	exit(1);
}

void	ft_perror()
{
//	ft_printf("%s\n", strerror(errno));
	perror("corewar");
	exit(1);
}
