#ifndef VM_H
# define VM_H

# include <stdio.h>
# include <fcntl.h>
# include <stdint.h>
# include "libft.h"
# include "op.h"

# define BUFF_SIZE	4096
# define INT_SIZE	4

typedef union	s_bits
{
	struct
	{
		uint8_t 	bit0 : 1;
		uint8_t 	bit1 : 1;
		uint8_t 	bit2 : 1;
		uint8_t 	bit3 : 1;
	};
	int8_t		num;
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




typedef	struct	s_player
{
	int8_t 		id;
	char		name[PROG_NAME_LENGTH];
	char		comment[COMMENT_LENGTH];
	int16_t		exec_size;
}				t_player;

typedef struct	s_players
{
	int8_t		number_of_players;
	t_player	*player;
	char		*path[MAX_PLAYERS];
	int8_t		flag_n[MAX_PLAYERS];
}				t_players;

typedef struct	s_cur
{
	int32_t			id;
	int8_t			carry;
	uint8_t			op_code;
	int				cycle_of_last_live;
	int16_t			cycles_to_do_op;
	int16_t			pc;					//position
	int8_t			byte_to_next_op;
	int32_t			reg[REG_NUMBER];
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
	int32_t		min_player_id;
	int32_t		max_player_id;
}				t_vm;

t_op			op_tab[17];

void	ft_cw_vm_handle(int ac, char **av, t_players *players, int *nbr_cycles);
void	ft_cw_vm_read(t_vm *vm, t_players *players);
char	*ft_create_buf(char *path);
void	ft_init_cursors(t_vm *vm, t_players *players);
void	ft_introducing(t_players *players);
void 	ft_battle(t_vm *vm, t_player *player);
void	ft_set_valid_func(int8_t (**type) (int8_t));
int		ft_valid_op_code_and_reg(t_vm *vm, t_cur *cursor, int8_t (**valid) (int8_t));
void	ft_init_op(void (**op) (t_types_code, t_vm *, t_cur *pCursor));
t_cur	*ft_copy_cursor(t_vm *vm, t_cur *cursor);
void	ft_endgame(t_vm *vm, t_player *player);
void	ft_cw_usage();
void	ft_error(int8_t id);
void	ft_perror();

#endif
