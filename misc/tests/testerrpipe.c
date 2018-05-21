#include <stdlib.h>
#include <unistd.h>

int		main(void)
{
	int			pfd[2];
	const char	*lsargs[5] = {"/bin/ls", "-l", "errfile", ".", NULL};
	const char	*catargs[3] = {"/bin/cat", "-e", NULL};
	pid_t		pid;
	
	pipe(pfd);
	pid = fork();
	if (pid == 0)
	{
		close(pfd[0]);
		close(STDOUT_FILENO);
		dup2(pfd[1], STDOUT_FILENO);
		close(STDERR_FILENO);
		dup2(STDOUT_FILENO, STDERR_FILENO);
		execve(*lsargs, (char**)lsargs, NULL);
		exit(0);
	}
	close(pfd[1]);
	pid = fork();
	if (pid == 0)
	{
		close(STDIN_FILENO);
		dup2(pfd[0], STDIN_FILENO);
		execve(*catargs, (char**)catargs, NULL);
		exit(0);
	}
	wait(NULL);
	return 0;
}
