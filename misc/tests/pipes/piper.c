/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piper.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 01:56:25 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/07 02:28:39 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int		main(int ac, char **av, char **env)
{
	char	*path1;
	char	*path2;
	char	*path3;
	char	*av1[5];
	char	*av2[5];
	char	*av3[5];

	char	**ptr;
	uint8_t	third;

	int		fd1[2];
	int		fd2[2];
	pid_t	pid1;
	pid_t	pid2;
	pid_t	pid3;

	setbuf(stdout, NULL);
	bzero(av1, sizeof(av1));
	bzero(av2, sizeof(av2));
	bzero(av3, sizeof(av3));
	path1 = av[1];
	av1[0] = path1;
	ptr = &av1[1];
	third = 0;
	for (int i = 2; i < ac; i++)
	{
		if (strcmp(av[i], "|") == 0)
		{
			if (third)
			{
				ptr = &av3[1];
				path3 = av[++i];
				av3[0] = path3;
			}
			else
			{
				ptr = &av2[1];
				path2 = av[++i];
				av2[0] = path2;
				third = 1;
			}
			continue ;
		}
		*(ptr++) = av[i];
	}

	(void)pipe(fd1);

	pid1 = fork();
	if (pid1 == 0)
	{
		(void)close(fd1[0]);
		(void)dup2(fd1[1], STDOUT_FILENO);
		(void)execve(path1, av1, env);
		exit(1);
	}

	(void)pipe(fd2);

	pid2 = fork();
	if (pid2 == 0)
	{
		(void)close(fd1[1]);
		(void)dup2(fd1[0], STDIN_FILENO);
		(void)close(fd2[0]);
		(void)dup2(fd2[1], STDOUT_FILENO);
		(void)execve(path2, av2, env);
		exit(1);
	}

	(void)close(fd1[0]);
	(void)close(fd1[1]);

	pid3 = fork();
	if (pid3 == 0)
	{
		(void)close(fd2[1]);
		(void)dup2(fd2[0], STDIN_FILENO);
		(void)execve(path3, av3, env);
		exit(1);
	}

	(void)close(fd2[0]);
	(void)close(fd2[1]);

	(void)waitpid(pid3, NULL, 0);
	printf("%s finished.\n", path3);
	(void)waitpid(pid2, NULL, 0);
	printf("%s finished.\n", path2);
	(void)waitpid(pid1, NULL, 0);
	printf("%s finished.\n", path1);
	return (0);
}
