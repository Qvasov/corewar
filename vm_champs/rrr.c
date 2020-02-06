#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main()
{
	int fd = open("zork.s", O_RDONLY);
	char *buf = (char *)malloc(30);
	bzero(buf, 30);
	int ret;
	while ((ret = read(fd, buf, 30)) > 0)
	{}
	write(1, buf, 30);
	return (1);
}
