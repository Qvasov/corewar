/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endgame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:17:58 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/28 17:17:59 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_endgame(t_vm *vm, t_champ **player)
{
	printf("Contestant %hhd, \"%s\", has won !\n",
			vm->last_player_id, player[vm->last_player_id - 1]->name);
}
