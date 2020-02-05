#ifndef VM_H
# define VM_H

# include <stdio.h>
# include <fcntl.h>
# include <stdint.h>
# include "libft.h"
# include "op.h"

# define BUFF_SIZE	4096
# define INT_SIZE	4

typedef struct		s_buf
{
	char			str[BUFF_SIZE];
	size_t 			i;
}					t_buf;

typedef union	s_bits
{
	struct
	{
		uint8_t 	bit0 : 1;
		uint8_t 	bit1 : 1;
		uint8_t 	bit2 : 1;
		uint8_t 	bit3 : 1;
	};
	uint8_t		num;
}				t_bits;

typedef union	u_types_code
{
	struct
	{
		uint8_t	arg4 : 2;
		uint8_t	arg3 : 2;
		uint8_t	arg2 : 2;
		uint8_t	arg1 : 2;
	};
	uint8_t 	num;
}				t_types_code;

typedef union	u_int
{
	char		byte[INT_SIZE];
	int			num;
}				t_int;




typedef	struct	s_champ
{
	char		*path;
	int8_t 		id;
	char		name[PROG_NAME_LENGTH];
	char		comment[COMMENT_LENGTH];
	int16_t		exec_size;
}				t_champ;

typedef struct	s_cur
{
	int				id;
	int8_t			carry;
	uint8_t			op_code;
	int32_t			cycle_of_last_live;
	int16_t			cycles_to_do_op;
	int16_t			pc;
	int				byte_to_next_op;
	int				reg[REG_NUMBER];
	struct s_cur	*prev;
	struct s_cur	*next;

}				t_cur;

typedef struct	s_vm
{
	uint8_t 	arena[MEM_SIZE];
	t_cur		*cursor;
	int			cursor_id;
	int			nbr_cycles;
	int64_t		cycle;
	int64_t		cycle_from_start;
	int64_t 	cycles_to_die;
	char		last_player_id;
	int			number_of_live;
	int			number_of_check;
	int8_t		size[4];
	int			min_player_id;
	int			num_of_players;
}				t_vm;

typedef struct	s_data
{
	t_vm		*vm;
	t_champ	*player[MAX_PLAYERS];
}				t_data;

extern	t_op			op_tab[17];

void	ft_parse(int ac, char **av, t_data *data);
void	ft_check_dump(char **av, t_vm *vm);
void	ft_check_num_player(char **av, t_data *data);
void	ft_read_players(t_vm *vm, t_champ *player);

void	ft_init_cursors(t_vm *vm, t_players *players);
void	ft_introducing(t_players *players);
void 	ft_battle(t_vm *vm, t_champ *player);
void	ft_init_valid_func(uint8_t (**type) (uint8_t, uint8_t));
int		ft_valid_op_code_and_reg(t_vm *vm, t_cur *cursor, uint8_t (**valid) (uint8_t, uint8_t));
void	ft_init_op(void (**op) (t_types_code, t_vm *, t_cur *pCursor));
void	live(t_types_code args_code, t_vm *vm, t_cur *cursor);
void	ld(t_types_code args_code, t_vm *vm, t_cur *cursor);
void	st(t_types_code args_code, t_vm *vm, t_cur *cursor);
void	add(t_types_code args_code, t_vm *vm, t_cur *cursor);
void	sub(t_types_code args_code, t_vm *vm, t_cur *cursor);
void	and(t_types_code args_code, t_vm *vm, t_cur *cursor);
void	or(t_types_code args_code, t_vm *vm, t_cur *cursor);
void	xor(t_types_code args_code, t_vm *vm, t_cur *cursor);
void	zjmp(t_types_code args_code, t_vm *vm, t_cur *cursor);
void	ldi(t_types_code args_code, t_vm *vm, t_cur *cursor);
void	sti(t_types_code args_code, t_vm *vm, t_cur *cursor);
void	fork_cw(t_types_code args_code, t_vm *vm, t_cur *cursor);
void	lld(t_types_code args_code, t_vm *vm, t_cur *cursor);
void	lldi(t_types_code args_code, t_vm *vm, t_cur *cursor);
void	lfork_cw(t_types_code args_code, t_vm *vm, t_cur *cursor);
void	aff(t_types_code args_code, t_vm *vm, t_cur *cursor);
void	ft_cycle(t_vm *vm, uint8_t (**valid) (uint8_t, uint8_t), void (**op) (t_types_code, t_vm *, t_cur *));
void	ft_check(t_vm *vm);
int		get_arg(uint8_t arg_code, int8_t arg_pos, uint8_t *arena, t_cur *cursor);
int		get_ind_value(t_int arg, t_cur *cursor, uint8_t *arena);
t_cur	*ft_copy_cursor(t_vm *vm, t_cur *cursor);
void	ft_endgame(t_vm *vm, t_champ *player);
void	ft_usage();
void 	ft_print_commands(t_vm *vm, t_cur *cursor);
void	ft_error(char *str);
void	ft_perror();

#endif
