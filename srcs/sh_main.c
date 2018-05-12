/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/12 02:06:03 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "sh.h"

int			exec_shell(const char *path)
{
	char		*line;
	int			fd;
	int			ret;

	fd = (!path) ? STDIN_FILENO : open(path, O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	ret = EXIT_SUCCESS;
	while (get_next_line(fd, &line) > 0)
	{
		ret = exec_cmds(line);
		set_env_var_n(NULL, "?", ret);
		ft_strdel(&line);
	}
	if (fd != STDIN_FILENO)
		close(fd);
	return (ret);
}

int			main(int ac, char **av)
{
	extern char	**environ;
	int			exval;

	switch_traps(TRUE);
	environ = ft_tabdup(environ);
	set_env_var(NULL, "SHELL", av[0]);
	getset_pwd_env();
	if (!getenv("PATH"))
		set_env_var(NULL, "PATH", SH_DEFAULT_PATH);
	set_env_var(NULL, "_", av[0]);
	if (ac > 1 || !ft_isatty(STDIN_FILENO))
		exval = exec_shell((ac > 1) ? av[1] : NULL);
	else
		exval = interactive_shell();
	return (exval);
}
