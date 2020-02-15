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
		(j == 0) ? printf("0x0000 : ") : printf("%#06x : ", j); // 32 октета в ряд
		while (++i < 64)
			printf("%.2x ", vm->arena[j + i]);
		printf("\n");
		j += i;
	}
	exit(1); // мб return лучше вставить
}

void	ft_battle(t_data *data)
{
	uint8_t	(*valid[4])(uint8_t, uint8_t);
	void	(*op[17])(t_data *, t_cur *);
	t_vm	*vm;

	ft_init_cursors(&data->vm, data->player); // создание и инициализация кареток
	ft_init_valid_func(valid);
	ft_init_op(op);
	(data->web_flag) ? web_init(data) : 0; //WEB
	(data->n_flag) ? visu_init() : 0; //NCURSES
	vm = &data->vm;
	(vm->nbr_cycles == 0) ? print_arena(vm) : 0;
	while (1)
	{
		if (vm->cycle == vm->cycles_to_die || vm->cycles_to_die <= 0)
			ft_checkout(data);
		if (vm->cursor == NULL)
			break;
		++vm->cycle;

		if (data->v_flag.bit1 && data->web_flag == 0)
			ft_printf("It is now cycle %d\n", vm->cycle_from_start + vm->cycle); // для фалга

		ft_cycle(data, valid, op);

		// что за чем ставить отследить
		(data->web_flag) ? web_cycle(data) : 0;

		(vm->nbr_cycles >= 0 && vm->cycle_from_start + vm->cycle == vm->nbr_cycles) ? print_arena(vm) : 0;

		(data->n_flag) ? render(vm, data->player) : 0;
	}
}
