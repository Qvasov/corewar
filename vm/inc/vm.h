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

//typedef	struct	s_path
//{
//	int 		id[4];
//	char		*path[4];
//}				t_path;

void	ft_cw_args(int ac, char **av, char **player_paths);

void	ft_cw_usage();
void	ft_error(int id);
void	ft_perror();

#endif
