#ifndef VM_H
# define VM_H

# include "libft.h"
# include "op.h"
# include <stdio.h>
# include <fcntl.h>

typedef	struct	s_player
{
	int 		id;
	char		name[PROG_NAME_LENGTH + 4];
	char		comment[COMMENT_LENGTH];
	int			exec_size;
	char		*exec_code;
}				t_player;

typedef	struct	s_path
{
	int 		flag_n[MAX_PLAYERS];
	char		*path[MAX_PLAYERS];
}				t_path;

void	ft_cw_args(int ac, char **av, t_path *paths, int *nbr_cycles);
void	ft_cw_read(t_path *paths, t_player **players, int number_of_players);

void	ft_cw_usage();
void	ft_error(int id);
void	ft_perror();

#endif
