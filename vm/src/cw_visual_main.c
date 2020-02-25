/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_visual_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:28:11 by laleta            #+#    #+#             */
/*   Updated: 2020/02/14 19:30:31 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_visual.h"

void	visu_init(void)
{
	initscr();
	cbreak();
	nodelay(stdscr, true);
	noecho();
	curs_set(0);
	keypad(stdscr, true);
	start_color();
	use_default_colors();
	init_color(COLOR_CYAN, 300, 350, 350);
	init_color(COLOR_BLUE, 20, 900, 1000);
	init_color(COLOR_YELLOW, 1000, 800, 20);
	init_color(COLOR_GREEN, 20, 1000, 400);
	init_color(COLOR_MAGENTA, 1000, 20, 900);
	init_pair(CW_DATA, COLOR_DEFAULT, COLOR_DEFAULT);
	init_pair(CW_ZERO, COLOR_CYAN, COLOR_DEFAULT);
	init_pair(CW_BORDER, COLOR_DEFAULT, COLOR_CYAN);
	init_pair(CW_PLAYER1, COLOR_BLUE, COLOR_DEFAULT);
	init_pair(CW_PLAYER2, COLOR_YELLOW, COLOR_DEFAULT);
	init_pair(CW_PLAYER3, COLOR_GREEN, COLOR_DEFAULT);
	init_pair(CW_PLAYER4, COLOR_MAGENTA, COLOR_DEFAULT);
	init_pair(CW_PL_UNDEF, COLOR_DEFAULT, COLOR_DEFAULT);
	init_pair(CW_LIVE, COLOR_MAGENTA, COLOR_DEFAULT);
}

void	put_memory(t_vm *vm)
{
	uint16_t	i;
	uint16_t	j;
	uint16_t	idx;

	i = 0;
	attron(COLOR_PAIR(CW_DATA));
	while (i < MEM_SIZE / 64)
	{
		j = 0;
		while (j < 64)
		{
			idx = i * 64 + j;
			if (vm->arena[idx] == 0)
				attron(COLOR_PAIR(CW_ZERO));
			mvprintw(idx / 64 + CW_BORDER_Y, (idx % 64) * 3 + CW_BORDER_X,
														"%02x", vm->arena[idx]);
			attron(COLOR_PAIR(CW_DATA));
			j++;
		}
		printw("\n");
		i++;
	}
	attroff(COLOR_PAIR(CW_DATA));
}

void	put_border(void)
{
	uint8_t	i;

	i = 0;
	attron(COLOR_PAIR(CW_BORDER));
	while (i <= CW_WIDTH)
	{
		if (i <= CW_HEIGHT)
		{
			mvprintw(i, 0, "  ");
			mvprintw(i, CW_WIDTH, "  ");
		}
		if (i <= CW_MEM_HEIGHT)
			mvprintw(i, CW_MEM_WIDTH, "  ");
		mvprintw(0, i, " ");
		mvprintw(CW_MEM_HEIGHT, i, " ");
		mvprintw(CW_HEIGHT, i, " ");
		i++;
	}
	attroff(COLOR_PAIR(CW_BORDER));
}

void	handle_event(uint8_t *pause, uint8_t *speed, t_vm *vm, t_champ *pl)
{
	int32_t	event;

	event = getch();
	if (event == 'p' || event == ' ')
		*pause = *pause ? 0 : 1;
	if (event == KEY_UP)
		*speed += *speed < 8 ? 1 : 0;
	if (event == KEY_DOWN)
		*speed -= *speed > 0 ? 1 : 0;
	if (event == 27 || event == 'q')
	{
		endwin();
		exit(1);
	}
	if (vm->cursor == NULL)
	{
		*pause = 1;
		attron(COLOR_PAIR(vm->last_player_id) | A_BOLD);
		mvprintw(CW_INFO2_Y + 15, CW_INFO_X, "winner: [%d] %.28s",
				vm->last_player_id, pl[vm->last_player_id - 1].name);
		attroff(COLOR_PAIR(vm->last_player_id) | A_BOLD);
	}
}

void	render(t_vm *vm, t_champ *player)
{
	uint8_t			render_loop;
	uint8_t			pause;
	static uint8_t	speed = 2;

	pause = 0;
	render_loop = 1;
	while (render_loop)
	{
		erase();
		put_memory(vm);
		put_operation();
		put_cursor(vm, vm->cursor, vm->num_of_players);
		put_infobox(vm, player, speed, pause);
		put_border();
		handle_event(&pause, &speed, vm, player);
		refresh();
		render_loop = pause;
	}
	usleep(g_delay[speed]);
}
