#include "vm.h"

static void	check_arg(int *i, int ac, char **av, char **paths)
{
	int		index;
	char	*dot;

	if (ft_strequ(av[*i], "-n"))
	{
		if (*i + 2 < ac)
		{
			index = ft_atoi_special(av[++(*i)]);
			if (index >= 1 && index <= MAX_PLAYERS)
				++(*i);
			else
				ft_cw_usage();
		}
		//получаем номер индекса в paths для следующего аргумента
		else
			ft_cw_usage();
	}
	dot = ft_strrchr(av[*i], '.');
	if (dot && ft_strequ(dot, ".cor"))
		;
	else
		ft_cw_usage();
}

static void	dump(int *i, int ac, char **av)
{
	if (ac >= 3 && ft_strequ(av[*i], "-dump"))
	{
		nbr_cycles = atoi_special(av[++(*i)]);
		++(*i);
	}
	else
		ft_cw_usage();
}

static void	init_paths(char **player_paths)
{
	int i;

	i = -1;
	while (++i < MAX_PLAYERS)
		player_paths[i] = NULL;
}

void		ft_cw_args(int ac, char **av, char **player_paths)
{
	int		i;
	int 	j;

	init_paths(player_paths);
	i = 0;
	j = -1;
	while (++i <= ac && ++j < MAX_PLAYERS)
	{
		(i == 1) ? dump(&i, ac, av) : 1;
		check_arg(&i, ac, av, player_paths);
		player_paths->path[j] = av[i];
		player_paths->id[j] = j + 1;
	}
}
