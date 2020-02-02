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

void	ft_battle(t_vm *vm, t_player *player)
{
//	uint8_t	(*valid[4])(uint8_t);
//	uint8_t	(*valid)(uint8_t);
//	valid = (uint8_t (*)(uint8_t))malloc(sizeof(uint8_t (*)(uint8_t)));
	void	(*op[17])(t_types_code, t_vm *, t_cur *);

	ft_init_valid_func(vm->valid);
	ft_init_op(op);
	while (++vm->cycle && vm->cursor)
	{
		ft_cycle(vm, vm->valid, op);
//		vm->cycle_from_start + vm->cycle == 2180 ? print_arena(vm) : 0;
		if (vm->cycle == vm->cycles_to_die || vm->cycles_to_die <= 0)
			ft_check(vm);
		if (vm->nbr_cycles >= 0 && vm->cycle_from_start + vm->cycle == vm->nbr_cycles)
		{
//						вывод дампа
			return ;
		}
	}
	ft_endgame(vm, player);
}
