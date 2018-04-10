/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_bltncmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 23:00:55 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/10 20:00:31 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"

static int	get_env_opt_code(char c)
{
	if (c == 'i')
		return (0x1);
	else
		return (-c);
	return (0);
}

static int	get_env_opts(int ac, char **av, int *idx)
{
	int				ret;
	int				new;
	unsigned int	sidx;

	ret = 0;
	if (ac == 1)
		return (0);
	while (av[*idx])
	{
		if (av[*idx][0] == '-')
		{
			sidx = 1;
			while (av[*idx][sidx])
			{
				if ((new = get_env_opt_code(av[*idx][sidx++])) < 0)
					return (new);
				ret |= new;
			}
			(*idx)++;
		}
		else
			break ;
	}
	return (ret);
}

static int	launch_utility(char **av, int idx, char **new_env)
{
	int				ret;
	t_cmd			*cmd;

	cmd = ft_cmdnew();
	cmd->c_argv = ft_tabdup((const char**)(av + idx));
	cmd->c_path = get_cmd_path(*cmd->c_argv, new_env);
	ret = exec_cmd(cmd, &new_env);
	ft_cmddel(&cmd);
	return (ret);
}

static int	usage(char a)
{
	ft_putstr_fd("env: illegal option -- ", STDERR_FILENO);
	ft_putchar_fd(a, STDERR_FILENO);
	ft_putendl_fd("\nusage: [-i]", STDERR_FILENO);
	ft_putendl_fd("       [name=value ...] [utility [argument ...]]", \
														STDERR_FILENO);
	return (EXIT_FAILURE);
}

int			env_bltn(int ac, char **av, char ***env, int outfd)
{
	char			**new_env;
	int				idx;
	int				opts;
	int				exval;

	exval = EXIT_SUCCESS;
	idx = 1;
	if ((opts = get_env_opts(ac, av, &idx)) < 0)
		return (usage(-opts));
	new_env = (opts & 0x1) ? ft_tabnew() : ft_tabdup((const char**)*env);
	while (ac > 1 && av[idx])
	{
		if (!ft_strchr(av[idx], '='))
			break ;
		set_env_from_str(&new_env, av[idx]);
		idx++;
	}
	(!av[idx]) ? ft_puttab_fd(new_env, NULL, outfd) \
		: (exval = launch_utility(av, idx, new_env));
	ft_tabfree(&new_env);
	return (exval);
}
