/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_bltncmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 23:00:55 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/06 06:01:48 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"

static int	launch_utility(char **av, int idx, char **new_env)
{
	int				ret;
	t_cmdnode		cmdnode;
	extern char		**environ;

	ft_bzero(&cmdnode, sizeof(t_cmdnode));
	cmdnode.stdout_fd = -1;
	cmdnode.stdin_fd = -1;
	cmdnode.c_av = ft_tabdup(av + idx);
	cmdnode.c_path = get_cmd_path(*cmdnode.c_av, environ);
	ret = exec_cmd(&cmdnode, NO, NULL, new_env);
	ft_tabfree(&cmdnode.c_av);
	free(cmdnode.c_path);
	return (ret);
}

static int	env_usage(char a)
{
	ft_putstr_fd("env: illegal option -- ", STDERR_FILENO);
	ft_putchar_fd(a, STDERR_FILENO);
	ft_putendl_fd("\nusage: [-i]\n"
			"       [name=value ...] [utility [argument ...]]", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int			env_bltn(int ac, char **av)
{
	extern char		**environ;
	char			**new_env;
	int				idx;
	int				opts;
	int				exval;

	idx = 1;
	if ((opts = ft_args_opts(av, &idx, "i", NULL)) < 0)
		return (env_usage((char)-opts));
	exval = EXIT_SUCCESS;
	new_env = (opts & 0x1) ? ft_tabnew() : ft_tabdup(environ);
	while (ac > 1 && av[idx])
	{
		if (!ft_strchr(av[idx], '='))
			break ;
		set_env_from_str(&new_env, av[idx]);
		idx++;
	}
	if (!av[idx])
		ft_puttab_fd(new_env, NULL, STDOUT_FILENO);
	else
		exval = launch_utility(av, idx, new_env);
	ft_tabfree(&new_env);
	return (exval);
}
