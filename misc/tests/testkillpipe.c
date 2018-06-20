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
	signal(SIGPIPE, &sighdl);
	while (1)
	{
		write(1, "hello\n", 6);
		sleep(1);
	}
	return 0;
}
