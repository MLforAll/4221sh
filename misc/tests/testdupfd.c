#include <unistd.h>
#include <string.h>

void	wrputs(int fd, const char *s)
{
	write(fd, s, strlen(s));
	write(fd, "\n", 1);
}

int		main(void)
{
	int	fd;

	fd = 3;
	dup2(STDOUT_FILENO, fd);
	wrputs(STDOUT_FILENO, "STDOUT_FILENO msg");
	close(STDOUT_FILENO);
	wrputs(STDOUT_FILENO, "STDOUT_FILENO msg2");
	wrputs(fd, "fd msg");
	return 0;
}
