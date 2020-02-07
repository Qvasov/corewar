/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_battle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:03:05 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/23 16:03:06 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_arena(t_vm *vm)
{
	int i;
	int j;
	j = 0;
	while (j < MEM_SIZE)
	{
		i = -1;
		(j == 0) ? printf("0x0000 : ") : printf("%#06x : ", j);
		while (++i < 64)
			printf("%.2x ", vm->arena[j + i]);
		printf("\n");
		j += i;
	}
	exit(1);
}

void	ft_battle(t_vm *vm, t_champ *player)
{
	uint8_t	(*valid[4])(uint8_t, uint8_t);
	void	(*op[17])(t_types_code, t_vm *, t_cur *);

	ft_init_cursors(vm, player); // создание и инициализация кареток
	ft_init_valid_func(valid);
	ft_init_op(op);
	while (vm->cursor)
	{
		if (vm->cycle == vm->cycles_to_die || vm->cycles_to_die <= 0)
			ft_checkout(vm);
		if (vm->nbr_cycles >= 0 && vm->cycle_from_start + vm->cycle == vm->nbr_cycles)
		{
			print_arena(vm);
			return ;
		}
		++vm->cycle;
		ft_printf("It is now cycle %d\n", vm->cycle_from_start + vm->cycle); // для фалга
		ft_cycle(vm, valid, op);
	}
	ft_endgame(vm, player);
}
