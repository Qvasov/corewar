/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_visual_cursor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:28:35 by laleta            #+#    #+#             */
/*   Updated: 2020/02/14 19:34:26 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_visual.h"

static void	put_progress_bar(uint64_t *cursor_cnt, uint8_t pl_cnt)
{
	uint8_t	i;
	uint8_t	width;

	i = 1;
	while (i <= pl_cnt)
	{
		width = cursor_cnt[i] <= 235 ? cursor_cnt[i] : 235;
		attron(COLOR_PAIR(i));
		mvprintw(CW_BAR_Y + 2 * (i - 1), CW_BORDER_X, "%*.d ", width,
																cursor_cnt[i]);
		attroff(COLOR_PAIR(i));
		i++;
	}
	attroff(A_BOLD | A_STANDOUT);
	mvprintw(CW_INFO2_Y + 7, CW_INFO_X + 24, "%lld", cursor_cnt[0]);
}

static void	put_last_live(int32_t *last_live, uint8_t pl_cnt)
{
	uint8_t	i;

	i = 0;
	attron(A_BOLD);
	while (i < pl_cnt)
	{
		mvprintw(CW_BORDER_Y + i * 5 + 3, CW_INFO_X + 24, "%d", last_live[i]);
		i++;
	}
	attroff(A_BOLD);
}

static void	put_player_oper(int32_t pl_nbr, t_cur *cursor)
{
	int8_t	oper;

	oper = cursor->op - 1;
	if (pl_nbr < 5 && oper >= 0 && oper < 16)
		mvprintw(CW_INFO3_Y + oper, CW_INFO_X + (pl_nbr - 1) * 10, "%s",
																g_oplist[oper]);
}

void		put_cursor(t_vm *vm, t_cur *cursor, int32_t pl_cnt)
{
	uint16_t		idx;
	int32_t			pl_nbr;
	t_player_cursor	pl_curs;

	ft_bzero(&pl_curs, sizeof(pl_curs));
	attron(A_BOLD | A_STANDOUT);
	while (cursor)
	{
		pl_nbr = -cursor->reg[0];
		pl_nbr = pl_nbr > 0 && pl_nbr <= pl_cnt ? pl_nbr : CW_PL_UNDEF;
		idx = cursor->pc % MEM_SIZE;
		attron(COLOR_PAIR(pl_nbr));
		mvprintw(idx / 64 + CW_BORDER_Y, (idx % 64) * 3 + CW_BORDER_X,
														"%02x", vm->arena[idx]);
		++pl_curs.cursor_cnt[pl_nbr];
		++pl_curs.cursor_cnt[0];
		if (pl_nbr < 5 && cursor->cycle_of_last_live > pl_curs.live[pl_nbr - 1])
			pl_curs.live[pl_nbr - 1] = cursor->cycle_of_last_live;
		put_player_oper(pl_nbr, cursor);
		attroff(COLOR_PAIR(pl_nbr));
		cursor = cursor->next;
	}
	put_progress_bar(pl_curs.cursor_cnt, pl_cnt);
	put_last_live(pl_curs.live, pl_cnt);
}
