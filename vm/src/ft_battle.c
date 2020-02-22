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

void	print_arena(t_data *data)
{
	int		i;
	int		j;
	int		oct;

	j = 0;
	oct = (data->o_flag == 1) ? 64 : 32;
	while (j < MEM_SIZE)
	{
		i = -1;
		ft_bprintf(&data->fstr, "0x%.4x : ", j);
		while (++i < oct)
			ft_bprintf(&data->fstr, "%.2hhx ", data->vm.arena[j + i]);
		ft_bprintf(&data->fstr, "\n");
		j += i;
	}
	exit(1);
}

void	ft_battle(t_data *data)
{
	t_vm	*vm;

	vm = &data->vm;
	ft_init_cursors(&data->vm, data->player); // создание и инициализация кареток
	ft_init_valid_func(data->valid);
	ft_init_op(data->op);
	(data->web_flag) ? web_init(data) : 0;	//WEB
	(data->nc_flag) ? visu_init() : 0;		//NCURSES
	(vm->nbr_cycles == 0) ? print_arena(data) : 0;
	while (1)
	{
		if (vm->cycle == vm->cycles_to_die || vm->cycles_to_die <= 0)
			ft_checkout(data);
		if (vm->cursor == NULL)
			break ;
		++vm->cycle;
		if ((ft_bit_check(data->v_flag, 1)) && data->web_flag == 0)
			flag_v2_c(data);
		ft_cycle(data);
		(vm->nbr_cycles >= 0 && vm->cycle_from_start +
			vm->cycle == vm->nbr_cycles) ? print_arena(data) : 0;
		(data->web_flag) ? web_cycle(data) : 0;
		(data->nc_flag) ? render(vm, data->player) : 0;
	}
}
