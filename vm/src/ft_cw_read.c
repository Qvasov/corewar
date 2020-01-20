#include "vm.h"

static long long	revbytes(long long num)
{
	unsigned char	byte;
	long long		tmp;
	size_t			i;

	tmp = 0;
	i = sizeof(int);
	while (i--)
	{
		byte = (char)num;
		tmp = tmp << 8;
		tmp += byte;
		num = num >> 8;
	}
	return (tmp);
}

void				ft_cw_read(t_path *paths, t_player **players, int number_of_players)
{
	t_player		player[number_of_players];
	union u_i
	{
		char b[4];
		int  i;
	} num;
//	int				num;
	int				fd;
	int 			i;

	i = -1;
	while (++i < number_of_players)
	{
		((fd = open(paths->path[i], O_RDONLY)) < 0) ? ft_perror() : 0;
		(read(fd, &num, 4) < 0) ? ft_perror() : 0; //считывание мэджика
		(revbytes(num.i) != COREWAR_EXEC_MAGIC) ? ft_error(1) : 0; //ошибка мэджика
		(read(fd, &player[i].name, PROG_NAME_LENGTH + 4) < 0) ? ft_perror() : 0; //считывание имени игрока
		(read(fd, &num.i, 4) < 0) ? ft_perror() : 0; //считывание размера исполняемого кода
		player[i].exec_size = (int)revbytes(num.i);
		(player[i].exec_size > CHAMP_MAX_SIZE) ? ft_error(1) : 0; //проверка на превышение размера чемпиона
		(read(fd, &player[i].comment, COMMENT_LENGTH + 4) < 0) ? ft_perror() : 0;
		(read(fd, &player[i].exec_code, player->exec_size) < 0) ? ft_perror() : 0;
	}
}

