#include "vm.h"


static void	check_arg(int *i, char **av, t_path *paths)
{
	char *dot;

	if (ft_strequ(av[*i], "-n"))
		;
	dot = ft_strrchr(av[*i], '.');
	if (dot && ft_strequ(dot, ".cor"))
		;
	else
		ft_usage();
}

static void	dump(int *i, int ac, char **av)
{
	if (ac >= 3 && ft_strequ(av[*i], "-dump"))
	{
		nbr_cycles = atoi_special(av[++(*i)]);
		++(*i);
	}
	else
		ft_usage();
}

void		ft_corewar_args(int ac, char **av, t_path *player_paths)
{
	int	i;
	int j;

	i = 0;
	j = -1;
	while (++i <= ac && ++j < MAX_PLAYERS)
	{
		(i == 1) ? dump(&i, ac, av) : 1;
		check_arg(&i, av, player_paths);
		player_paths->path[j] = av[i];
		player_paths->id[j] = j + 1;
	}


}
