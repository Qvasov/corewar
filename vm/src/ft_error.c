#include "vm.h"
#include <errno.h>

void	ft_error(int id)
{
	write (2, "ERROR\n", 6);
	exit(id);
}

void	ft_perror()
{
	ft_printf("%s\n", strerror(errno));
	perror("corewar");
	exit (1);
}
