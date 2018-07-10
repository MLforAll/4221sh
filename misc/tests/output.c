#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int	fd = open("/Users/Kelian/Desktop/testfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (42)
	{
		write(fd, "salut\n", 6);
		sleep(1);
	}
	close(fd);
	return 0;
}
