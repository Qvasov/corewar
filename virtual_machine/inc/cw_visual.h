/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_visual.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 20:00:42 by laleta            #+#    #+#             */
/*   Updated: 2020/02/14 19:41:01 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_VISUAL_H
# define CW_VISUAL_H

# include "vm.h"

# define CW_PLAYER1		1
# define CW_PLAYER2		2
# define CW_PLAYER3		3
# define CW_PLAYER4		4
# define CW_PL_UNDEF	5
# define CW_ZERO		6
# define CW_LIVE		7
# define CW_DATA		8
# define CW_BORDER		9
# define COLOR_DEFAULT	-1

# define CW_WIDTH		242
# define CW_HEIGHT		77
# define CW_MEM_WIDTH	197
# define CW_MEM_HEIGHT	67
# define CW_BORDER_X	4
# define CW_BORDER_Y	2

# define CW_INFO_X		201
# define CW_BAR_Y		69
# define CW_INFO2_Y		26
# define CW_INFO3_Y		50

typedef struct			s_player_cursor
{
	uint64_t			cursor_cnt[6];
	int32_t				live[4];
}						t_player_cursor;

static const uint32_t	g_delay[] =
{
	1000000, 100000, 10000, 1000, 500, 300, 100, 10, 0
};

static const char		*g_oplist[] =
{
	"   live   ", "    ld    ", "    st    ", "    add   ",
	"    sub   ", "    and   ", "    or    ", "    xor   ",
	"   zjmp   ", "    ldi   ", "    sti   ", "   fork   ",
	"    lld   ", "   lldi   ", "   lfork  ", "    aff   "
};

void					render(t_vm *vm, t_champ *player);
void					put_operation(void);
void					put_cursor(t_vm *vm, t_cur *cursor, int32_t pl_cnt);
void					handle_event(uint8_t *pause, uint8_t *speed, t_vm *vm,
						t_champ *pl);
void					put_infobox(t_vm *vm, t_champ *pl, uint8_t speed,
						uint8_t pause);
void					put_border(void);
void					put_memory(t_vm *vm);
void					visu_init(void);

#endif
