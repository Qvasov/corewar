#include "vm.h"

void	ft_error(int id)
{
	write (2, "ERROR\n", 6);
	exit(id);
}

void	ft_perror()
{
	perror("lem-in: ");
	exit (1);
}
