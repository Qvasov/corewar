/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:31:29 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/25 14:31:30 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_usage(void)
{
	ft_printf("./corewar [-dump nbr_cycles -v N | -nc | -w] [-o] [-l]"
		" [[-n number] champion1.cor] ...\n\n"
	"\t-dump nbr_cycles\t: "
		"Dump the memory on the standard output and quit the game\n"
	"\t-n number\t\t\t: Sets the number of the next player\n"
	"\t-v N\t\t\t\t:"
		" Verbosity levels, can be added together to enable several\n"
	"\t\t\t\t\t\t - 0  Show only essentials\n"
	"\t\t\t\t\t\t - 1   Show lives\n"
	"\t\t\t\t\t\t - 2   Show cycles\n"
	"\t\t\t\t\t\t - 4   Show operations (Params are NOT literal ...)\n"
	"\t\t\t\t\t\t - 8   Show deaths\n"
	"\t\t\t\t\t\t - 16  Show PC movements (Except for jumps)\n"
	"\t-nc\t\t\t\t\t: Ncurses output mode\n"
	"\t-w\t\t\t\t\t: Web output mode\n"
	"\t-l\t\t\t\t\t: Hide display live instruction\n"
	"\t-o\t\t\t\t\t: Original behaviour\n");
	exit(0);
}
