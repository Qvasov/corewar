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

static void	init_players_number(t_players *players)
{
	int	i;

	i = 0;
	while (players->path[i])
		++i;
	players->number_of_players = i;
	players->player = malloc(sizeof(t_player) * i);
}

int main(int ac, char **av)
{
	t_players	players;
	t_vm		vm;

//	nbr_cycles = 0; //хз сколько по умолчанию (если -dump не прописан) и куда его записывать
	(ac <= 1) ? ft_cw_usage() : 0;
	init_players(&players); // создание структуры players
	ft_cw_vm_handle(ac, av, &players, &vm.nbr_cycles); //хендлинг аргументов ./corewar
	init_players_number(&players); //инициализация кол-ва игроков
	ft_cw_vm_read(&players); //считывание байт-кода и разбор на состоваляющие
	ft_init_arena(&vm, &players); //создание и инициализация арены
	ft_init_cursors(&vm, players.number_of_players); // создание и инициализация кареток
//	ft_battle();
	return (0);
}

//запись по индексу которые я получаю из -n, остальные заполняются по порядку.
