/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 21:26:55 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/24 21:26:56 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stdio.h>
# include <fcntl.h>
# include <stdint.h>
# include <ncurses.h>
# include "libft.h"
# include "op.h"
# include "types.h"

typedef	struct		s_champ
{
	char			*path;
	int8_t			id;
	char			name[PROG_NAME_LENGTH + 4];
	char			comment[COMMENT_LENGTH + 4];
	int				exec_size;
}					t_champ;

typedef struct		s_cur
{
	int				id;
	int8_t			carry;
	uint8_t			op;
	int32_t			cycle_of_last_live;
	int16_t			cycles_to_do_op;
	int16_t			pc;
	int				byte_to_next_op;
	int				reg[REG_NUMBER];
	struct s_cur	*prev;
	struct s_cur	*next;

}					t_cur;

typedef struct		s_vm
{
	uint8_t			arena[MEM_SIZE];
	t_cur			*cursor;
	uint64_t		cursor_id;
	int				nbr_cycles;
	int64_t			cycle;
	int64_t			cycle_from_start;
	int64_t			cycles_to_die;
	int				last_player_id;
	uint64_t		number_of_live;
	int				number_of_check;
	int				min_player_id;
	int				num_of_players;
}					t_vm;

typedef struct		s_data
{
	t_vm			vm;
	t_champ			player[MAX_PLAYERS + 1];
	int8_t			size[4];
	uint8_t			(*valid[4])(uint8_t, uint8_t);
	void			(*op[17])(struct s_data *, t_cur *);
	t_visu			web;
	t_fstr			fstr;
	int				v_flag;
	int				web_flag;
	int				nc_flag;
	int				o_flag;
	int				l_flag;
}					t_data;

extern	t_op		g_op[17];

void				ft_parse(int ac, char **av, t_data *data);
void				ft_check_dump(char **av, t_vm *vm);
void				ft_check_num_player(char **av, t_data *data);
void				ft_check_v(char **av, t_data *data);
void				ft_read_valid_players(t_vm *vm, t_champ *player,
					int max_size);
void				ft_introducing(t_data *data);
void				ft_battle(t_data *data);
void				ft_init_cursors(t_vm *vm, t_champ *player);
void				ft_init_valid_func(uint8_t (**type) (uint8_t, uint8_t));
void				ft_init_op(void (**op) (t_data *, t_cur *cursor));
void				ft_checkout(t_data *data);
void				ft_cycle(t_data *data);
int					ft_valid_op_code_and_reg(t_data *data, t_cur *cursor);
void				live(t_data *data, t_cur *cursor);
void				ld(t_data *data, t_cur *cursor);
void				st(t_data *data, t_cur *cursor);
void				add(t_data *data, t_cur *cursor);
void				sub(t_data *data, t_cur *cursor);
void				and(t_data *data, t_cur *cursor);
void				or(t_data *data, t_cur *cursor);
void				xor(t_data *data, t_cur *cursor);
void				zjmp(t_data *data, t_cur *cursor);
void				ldi(t_data *data, t_cur *cursor);
void				sti(t_data *data, t_cur *cursor);
void				fork_cw(t_data *data, t_cur *cursor);
void				lld(t_data *data, t_cur *cursor);
void				lldi(t_data *data, t_cur *cursor);
void				lfork_cw(t_data *data, t_cur *cursor);
void				aff(t_data *data, t_cur *cursor);
void				get_args(t_int *arg, t_types_code args_code, t_cur *cursor,
					t_data *data);
int					get_arg(uint8_t arg_code, int8_t arg_pos, uint8_t *arena,
					t_cur *cursor);
int					get_ind_value(t_int arg, t_cur *cursor, t_data *data);
t_cur				*ft_copy_cursor(t_data *data, t_cur *cursor);
void				ft_endgame(t_data *data);
void				ft_free(t_data *data);
void				ft_usage();
void				ft_error(char *str);
void				ft_perror(t_data *data);

void				flag_v1(t_data *data, int num_of_player);
void				flag_v2_c(t_data *data);
void				flag_v2_ctd(t_data *data);
void				flag_v4(const t_int *args, t_types_code args_code,
					t_data *data, t_cur *cursor);
void				flag_v8(t_data *data, t_cur *cursor);
void				flag_v16(t_data *data, t_cur *cursor);

void				web_init(t_data *data);
void				web_cur_parse(t_data *data, t_cur *cursor);
void				web_cur_before_do(t_data *data, t_cur *cursor);
void				web_cur_after_do(t_data *data, t_cur *cursor);
void				web_cycle(t_data *data);
void				ft_web_free(t_data *data);

void				render(t_vm *vm, t_champ *player);
void				visu_init(void);

#endif
