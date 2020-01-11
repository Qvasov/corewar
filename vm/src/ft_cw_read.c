#include "vm.h"

void		ft_cw_read(t_path *paths, int number_of_players)
{
	t_player	player[number_of_players];
	char		buf[4096 + 1];
	int			fd;
	int 		i;

	i = -1;
	while (paths->path[++i])
	{
		(fd = open(paths->path[i], O_RDONLY) < 0) ? ft_perror() : 0;

		(read(fd, buf, 4 * 2) < 0) ? ft_perror() : 0;
		valid_magic(buf);

		(read(fd, buf, PROG_NAME_LENGTH * 2) < 0) ? ft_perror() : 0;
		player_name();
		(lseek(fd, 4 * 2, SEEK_CUR) < 0) ? ft_perror() : 0;

		(read(fd, buf, 4 * 2) < 0) ? ft_perror() : 0;
		exec_size();

		(read(fd, buf, COMMENT_LENGTH * 2) < 0) ? ft_perror() : 0;
	}
}
//
// Created by Donn Bennie on 11/01/2020.
//

