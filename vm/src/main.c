#include "vm.h"

int main(int ac, char **av)
{
	t_path	player_paths;

	ft_corewar_args(ac, av, &player_paths);
	ft_valid();
	ft_arena();
	return (0);
}