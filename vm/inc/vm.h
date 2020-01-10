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
	int 		id[4];
	char		*path[4];
}				t_path;

void	ft_corewar_args(int ac, char **av, t_path *player_paths);

void	ft_usage();
void	ft_error(int id);
void	ft_perror();

#endif
