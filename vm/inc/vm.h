#ifndef VM_H
# define VM_H

# include "libft.h"
# include "op.h"
# include <stdio.h>

typedef	struct	s_player
{
	int 			id;
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	struct s_player	*next;
	struct s_player	*prev;
}				t_player;

typedef	struct	s_path
{
	int 		flag_n[MAX_PLAYERS];
	char		*path[MAX_PLAYERS];
}				t_path;

void	ft_cw_args(int ac, char **av, t_path *paths, int *nbr_cycles);

void	ft_cw_usage();
void	ft_error(int id);
void	ft_perror();

#endif
