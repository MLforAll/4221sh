#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

static void sighdl(int sigc)
{
	if (sigc != SIGPIPE)
		return ;
	signal(SIGPIPE, SIG_DFL);
	write(2, "SIGPIPE\n", 8);
	raise(SIGPIPE);
}

int main(void)
{
	char	buff[32];
	ssize_t	rb;

	signal(SIGPIPE, &sighdl);
	while (1)
	{
		rb = read(0, buff, 32);
		write(1, buff, rb);
	}
	return 0;
}
