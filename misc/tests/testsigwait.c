#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static void	myputs(const char *s)
{
	write(1, s, strlen(s));
}

static void	sighdl(int sigc)
{
	(void)sigc;
	myputs("catched!\n");
}

int		main(void)
{
	const char	*sleepav[] = {"/bin/sleep", "10", NULL};
	pid_t		pid;

	signal(SIGCHLD, &sighdl);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGCHLD, SIG_DFL);
		execve(*sleepav, (char**)sleepav, NULL);
		exit(1);
	}
	wait(NULL);
	return (0);
}
