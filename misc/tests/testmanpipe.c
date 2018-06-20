#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int		main(int ac, char **av)
{
	int			pfd[2];
	char		*av1[2];
	char		*av2[2];
	pid_t		pid[2];

	if (ac < 2)
		return 1;
	bzero(av1, sizeof(av1));
	bzero(av2, sizeof(av2));
	*av1 = av[1];
	*av2 = av[2];
	pipe(pfd);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		close(pfd[0]);
		close(STDOUT_FILENO);
		dup2(pfd[1], STDOUT_FILENO);
		execve(av[1], av1, NULL);
		exit(0);
	}
	close(pfd[1]);
	pid[1] = fork();
	if (pid[1] == 0)
	{
		close(STDIN_FILENO);
		dup2(pfd[0], STDIN_FILENO);
		execve(av[2], av2, NULL);
		exit(0);
	}
	close(pfd[0]);
	waitpid(pid[1], NULL, 0);
	waitpid(pid[0], NULL, 0);
	return 0;
}
