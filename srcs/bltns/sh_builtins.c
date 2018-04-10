/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:26:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/10 20:02:34 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

int		echo_bltn(int ac, char **av, char ***env, int outfd)
{
	int		nonl;

	(void)env;
	nonl = 0;
	if (ac > 1 && ft_strcmp(av[1], "-n") == 0)
	{
		nonl = 1;
		av++;
	}
	while (*(++av))
	{
		ft_putstr_fd(*av, outfd);
		if (*(av + 1))
			ft_putchar_fd(' ', outfd);
	}
	if (!nonl)
		ft_putchar_fd('\n', outfd);
	return (EXIT_SUCCESS);
}

int		setenv_bltn(int ac, char **av, char ***env, int outfd)
{
	if (ac > 3)
		return (sh_err(SH_ERR_TMARG, "setenv", NULL));
	if (ac == 1)
	{
		ft_puttab_fd(*env, NULL, outfd);
		return (EXIT_SUCCESS);
	}
	if (!ft_isalpha(*av[1]) || ft_strchrf(av[1], '=')
		|| (ac == 3 && ft_strchr(av[1], '=')))
		return (sh_err(SH_ERR_INVID, av[0], av[1]));
	if (ac == 3)
		set_env_var(env, av[1], av[2]);
	else
		set_env_from_str(env, av[1]);
	return (EXIT_SUCCESS);
}

int		unsetenv_bltn(int ac, char **av, char ***env, int outfd)
{
	int		idx;

	(void)outfd;
	if (ac == 1)
		return (EXIT_FAILURE);
	if (!ft_isalpha(*av[1]) || ft_strchrf(av[1], '=')
		|| (ac == 3 && ft_strchr(av[1], '=')))
		return (sh_err(SH_ERR_INVID, av[0], av[1]));
	idx = 0;
	while (idx < ac)
		del_env_var(env, av[idx++]);
	return (EXIT_SUCCESS);
}

int		exit_bltn(int ac, char **av, char ***env, int outfd)
{
	char	*last_cmd_ret;

	(void)outfd;
	if (ac > 2)
		return (sh_err(SH_ERR_TMARG, av[0], NULL));
	if (ac == 1)
	{
		last_cmd_ret = get_env_var(*env, "?");
		exit((last_cmd_ret) ? ft_atoi(last_cmd_ret) : EXIT_SUCCESS);
	}
	if (!ft_strisnumeric(av[1]))
		exit(sh_err_ret(SH_ERR_NUMARG, av[0], av[1], 255));
	exit(ft_atoi(av[1]));
	return (EXIT_SUCCESS);
}

int		source_bltn(int ac, char **av, char ***env, int outfd)
{
	(void)outfd;
	if (ac == 1)
		return (EXIT_FAILURE);
	exec_shell(av[1], env);
	return (EXIT_SUCCESS);
}
