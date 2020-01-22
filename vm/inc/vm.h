#ifndef VM_H
# define VM_H

# include "libft.h"
# include "op.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdint.h>

# define BUFF_SIZE	4096

typedef union	u_int
{
	char		byte[sizeof(int)];
	int			num;
}				t_int;

typedef	struct	s_player
{
	int8_t 		id;
	char		name[PROG_NAME_LENGTH + 4];
	char		comment[COMMENT_LENGTH];
	int16_t		exec_size;
	char		exec_code[CHAMP_MAX_SIZE];
}				t_player;

typedef struct	s_players
{
	int8_t		number_of_players;
	t_player	*player;
	char		*path[MAX_PLAYERS];
	int8_t		flag_n[MAX_PLAYERS];
}				t_players;

typedef struct	s_cursor
{
	int32_t			id;
	int8_t			carry;
	int				op_code;
	int				cycle_of_last_live;
	int16_t			cycles_to_do_op;
	int16_t			position;
	uint8_t			byte_step;
	int				reg[REG_NUMBER];
	struct s_cursor	*next;
}				t_cursor;

typedef struct	s_vm
{
	char 		arena[MEM_SIZE];
	t_cursor	*cursor;
	int			cursor_id;
	int			nbr_cycles;
	size_t		cycles_from_start;
	size_t		cycles_to_die;
	int8_t		last_player_id;
	int			number_of_live_operations;

}				t_vm;

void	ft_cw_vm_handle(int ac, char **av, t_players *players, int *nbr_cycles);
void	ft_cw_vm_read(t_players *players);
char	*ft_create_buf(char *path);
void	ft_init_arena(t_vm *vm, t_players *players);
void	ft_init_cursors(t_vm *vm, t_players *players);

void	ft_cw_usage();
void	ft_error(int8_t id);
void	ft_perror();

#endif
