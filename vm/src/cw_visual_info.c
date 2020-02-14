/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_visual_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:28:54 by laleta            #+#    #+#             */
/*   Updated: 2020/02/14 21:47:29 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_visual.h"

static void	put_player_info(t_vm *vm, t_champ *pl)
{
	uint8_t		i;
	uint8_t		pl_nbr;
	const char	s[] = " ";

	i = 0;
	pl_nbr = vm->num_of_players;
	while (i < pl_nbr)
	{
		attron(COLOR_PAIR(i + 1));
		attron(A_BOLD | A_STANDOUT);
		mvprintw(CW_BORDER_Y + i * 5, CW_INFO_X, " PLAYER [%d]%28.s", i + 1, s);
		attroff(A_STANDOUT);
		mvprintw(CW_BORDER_Y + i * 5 + 1, CW_INFO_X, "%.40s", pl[i].name);
		attroff(A_BOLD);
		mvprintw(CW_BORDER_Y + i * 5 + 2, CW_INFO_X, "%.40s", pl[i].comment);
		attroff(COLOR_PAIR(i + 1));
		mvprintw(CW_BORDER_Y + i * 5 + 3, CW_INFO_X, "LAST LIVE CYCLE");
		i++;
	}
}

void		put_infobox(t_vm *vm, t_champ *player, uint8_t speed, uint8_t pause)
{
	attron(COLOR_PAIR(CW_DATA));
	mvprintw(CW_INFO2_Y + 0, CW_INFO_X, "CYCLE:			%d", vm->cycle);
	mvprintw(CW_INFO2_Y + 1, CW_INFO_X, "CYCLE TO DIE:		%d",
														vm->cycles_to_die);
	mvprintw(CW_INFO2_Y + 2, CW_INFO_X, "CYCLE FROM START:	%d",
											vm->cycle_from_start + vm->cycle);
	mvprintw(CW_INFO2_Y + 4, CW_INFO_X, "LIVE COUNT:		%d",
														vm->number_of_live);
	mvprintw(CW_INFO2_Y + 5, CW_INFO_X, "CHECK COUNT:		%d",
														vm->number_of_check);
	mvprintw(CW_INFO2_Y + 7, CW_INFO_X, "PROCESSES:");
	mvprintw(CW_INFO2_Y + 11, CW_INFO_X, "SPEED: %d", speed);
	if (pause)
	{
		attron(A_BOLD | A_STANDOUT);
		mvprintw(CW_INFO2_Y + 11, CW_INFO_X + 24, "     PAUSE     ");
		attroff(A_BOLD | A_STANDOUT);
	}
	attroff(COLOR_PAIR(CW_DATA));
	put_player_info(vm, player);
}

void		put_operation(void)
{
	uint8_t	i;
	uint8_t	j;

	i = 0;
	attron(COLOR_PAIR(CW_ZERO));
	while (i < 16)
	{
		j = 0;
		while (j < 4)
		{
			mvprintw(CW_INFO3_Y + i, CW_INFO_X + j * 10, "%s", g_oplist[i]);
			j++;
		}
		printw("\n");
		i++;
	}
	attroff(COLOR_PAIR(CW_ZERO));
}
