/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/05 00:44:16 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "sh.h"

int			exec_shell(const char *path, char ***env)
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
		ret = exec_cmds(line, env);
		set_env_var_n(env, "?", ret);
		ft_strdel(&line);
	}
	if (fd != STDIN_FILENO)
		close(fd);
	return (ret);
}

int			main(int ac, char **av, char **environ)
{
	char		**env;
	int			exval;

	switch_traps(TRUE);
	env = (environ) ? ft_tabdup((const char**)environ) : ft_tabnew();
	set_env_var(&env, "SHELL", av[0]);
	getset_pwd_env(&env);
	if (!get_env_var(env, "PATH"))
		set_env_var(&env, "PATH", SH_DEFAULT_PATH);
	set_env_var(&env, "_", av[0]);
	if (ac > 1 || !ft_isatty(STDIN_FILENO))
		exval = exec_shell((ac > 1) ? av[1] : NULL, &env);
	else
		exval = interactive_shell(&env);
	ft_tabfree(&env);
	return (exval);
}
