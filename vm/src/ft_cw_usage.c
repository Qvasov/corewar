#include "vm.h"

void	ft_cw_usage()
{
	write(1, "./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...\n", 61);
	exit(0);
}
