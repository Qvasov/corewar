#include "vm.h"

static int exec_size(char *str)
{
	t_int exec;
	int i;

	i = 4;
	while (i--)
		exec.byte[i] = str[3 - i];
	return (exec.num);

}

static void	valid_magic(char *str)
{
	t_int	magic;
	int		i;

	i = 4;
	while (i--)
		magic.byte[i] = str[3 - i];
	(magic.num != COREWAR_EXEC_MAGIC) ? ft_error(1) : 0; //ошибка мэджика
}

void		ft_cw_read(t_path *paths, t_player **players, int number_of_players)
{
	t_player	player[number_of_players];
	int 		i;
	char		*str;

	i = -1;
	while (++i < number_of_players)
	{
		str = ft_create_buf(paths->path[i]);
		valid_magic(str); //проверка magic
		ft_memcpy(player[i].name, &str[4], PROG_NAME_LENGTH); //считывание имени игрока
		player[i].exec_size = exec_size(&str[PROG_NAME_LENGTH + 8]); //считывание размера исполняемого кода
		(player[i].exec_size > CHAMP_MAX_SIZE) ? ft_error(1) : 0; //проверка на превышение размера чемпиона
		ft_memcpy(player[i].comment, &str[PROG_NAME_LENGTH + 12], COMMENT_LENGTH); //считывание коммента игрока
		ft_memcpy(player[i].exec_code, &str[PROG_NAME_LENGTH + COMMENT_LENGTH + 12], player[i].exec_size);
		char tmp[player[i].exec_size];
		ft_memcpy(tmp, player[i].exec_code, player[i].exec_size);
	}
}
