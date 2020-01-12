#include "vm.h"

void		ft_cw_read(t_path *paths, int number_of_players)
{
	t_player	player[number_of_players];
	union
	{
		char	buf[4];
		int		num;
	}			magic;
	int			fd;
	int 		i;

	i = -1;
	while (paths->path[++i])
	{
		((fd = open(paths->path[i], O_RDONLY)) < 0) ? ft_perror() : 0;
		(read(fd, magic.buf, 4) < 0) ? ft_perror() : 0; //считывание мэджика
	тут	(magic.num != COREWAR_EXEC_MAGIC) ? ft_error(1) : 0; //ошибка мэджика
		(read(fd, player->name, PROG_NAME_LENGTH + 4) < 0) ? ft_perror() : 0; //считывание имени игрока
		(read(fd, &player->exec_size, 4) < 0) ? ft_perror() : 0; //считывание размера исполняемого кода
		(player->exec_size > CHAMP_MAX_SIZE) ? ft_error(1) : 0; //проверка на превышение размера чемпиона
		(read(fd, player->comment, COMMENT_LENGTH + 4) < 0) ? ft_perror() : 0;
		(read(fd, player->exec_code, player->exec_size) < 0) ? ft_perror() : 0;
	}
}

