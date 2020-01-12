#include "vm.h"

static void	dump(int *i, int ac, char **av, int *nbr_cycles)
{
	if (ac >= 3 && ft_strequ(av[*i], "-dump"))
	{
		ft_satoi(av[++(*i)], nbr_cycles); // проверка на число, на оишибку
		++(*i);
	}
//	else
//		ft_cw_usage();
}

static int	player_number(int *i, int ac, char **av)
{
	int		index;
	int		len;

	index = 0;
	(*i < ac) ? 0 : ft_cw_usage(); //проверка на существование текущего аргумента
	if (ft_strequ(av[*i], "-n"))
	{
		(*i + 2 < ac) ? 0 : ft_cw_usage(); //проверка на существование слудующих аргументов для флага -n
		index = ft_satoi(av[++(*i)], &len); // проверка на ошибку и на буквыв строке (спросить у димаса)
		++(*i);
	}
	return (index);
}

static char *player_file(char *arg)
{
	char	*dot;

	//проверка на существование текущего аргумента прошла в функции player_number
	dot = ft_strrchr(arg, '.');
	if (!dot || !ft_strequ(dot, ".cor"))
		ft_cw_usage();
	return (arg);
}

static void	id_not_zero(char *arg, t_path *paths, int id)
{
	char *tmp1;
	char *tmp2;

	if (paths->flag_n[id - 1] == 0 && paths->path[id - 1] == NULL)
	{
		paths->path[id - 1] = player_file(arg);
		paths->flag_n[id - 1] = 1;
	}
	else if (paths->flag_n[id - 1] == 0 && paths->path[id - 1])
	{
		tmp1 = paths->path[id - 1];
		paths->path[id - 1] = player_file(arg);
		paths->flag_n[id - 1] = 1;
		while (++id <= MAX_PLAYERS)
			if (paths->flag_n[id - 1] == 0)
			{
				tmp2 = paths->path[id - 1];
				paths->path[id - 1] = tmp1;
				tmp1 = tmp2;
			}
	}
	else
		ft_error(1); //повторная запись игрока с тем же номером
}

void		ft_cw_args(int ac, char **av, t_path *paths, int *nbr_cycles)
{
	int		i;
	int 	j;
	int		num;
	int		id;

	i = 0;
	j = 0;
	num = 0;
	while (++j <= MAX_PLAYERS && ++i < ac)
	{
		(i == 1) ? dump(&i, ac, av, nbr_cycles) : 0;
		id = player_number(&i, ac, av);
		if (id == 0)
		{
			while (++num <= MAX_PLAYERS)
				if (paths->path[num - 1] == NULL)
				{
					paths->path[num - 1] = player_file(av[i]);
					break;
				}
			(num > MAX_PLAYERS) ? ft_error(1) : 0; //Превышение максимального кол-ва игроков
		}
		else if (id >= 1 && id <= MAX_PLAYERS)
			id_not_zero(av[i], paths, id);
		else if (id > MAX_PLAYERS)
			ft_error(1); // превышение по номеру игрока
	}
	(i + 1 < ac) ? ft_cw_usage() : 0;// проверка на аргументы после 4 игрока
}
