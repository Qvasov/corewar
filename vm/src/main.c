/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 16:02:31 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/21 19:49:24 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	init_arena(t_vm *vm, int8_t num)
{
	ft_bzero(vm->arena, MEM_SIZE);
	vm->cursor = NULL;
	vm->cursor_id = 0;
	vm->cycle = 0;
	vm->cycle_from_start = 0;
	vm->cycles_to_die = 1536;
	vm->last_player_id = num;
	vm->number_of_live = 0;
	vm->size[0] = 0;
	vm->size[REG_CODE] = 1;
	vm->size[DIR_CODE] = DIR_SIZE;
	vm->size[IND_CODE] = IND_SIZE;
	vm->min_player_id = 1;
	vm->max_player_id = num;
}

static void	init_players_number(t_players *players)
{
	int	i;

	i = 0;
	while (players->path[i])
		++i;
	players->number_of_players = i;
	players->player = malloc(sizeof(t_player) * i);
}

static void	init_players(t_players *players)
{
	int i;

	players->number_of_players = 0;
	players->player = NULL;
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		players->path[i] = NULL;
		players->flag_n[i] = 0;
	}
}

int main(int ac, char **av)
{
	t_players	players;
	t_vm		vm;

	(ac <= 1) ? ft_cw_usage() : 0;
	init_players(&players); // создание структуры players
	ft_cw_vm_handle(ac, av, &players, &vm.nbr_cycles); //хендлинг аргументов ./corewar
	init_players_number(&players); //инициализация кол-ва игроков
	init_arena(&vm, players.number_of_players); //создание и инициализация арены
	ft_cw_vm_read(&vm, &players); //считывание байт-кода и разбор на состоваляющие
	ft_init_cursors(&vm, &players); // создание и инициализация кареток
	ft_introducing(&players);
	ft_battle(&vm, players.player);
//	free(); //всё остальное //free players
	return (0);
}

// добавить инит курсорс в мейн под статиком
//запись кода сразу в арену а не переменую причем замолоченную.
