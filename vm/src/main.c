#include "vm.h"

int main(int ac, char **av)
{
	char	*player_paths[MAX_PLAYERS];

	if (ac <= 1)
		ft_cw_usage();
	ft_cw_args(ac, av, player_paths);
	ft_valid();
	ft_arena();
	return (0);
}

//запись по индексу которые я получаю из -n, остальные заполняются по порядку.