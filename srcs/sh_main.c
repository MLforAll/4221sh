/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/29 02:35:27 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"

char		*getset_pwd_env(void)
{
	char			*ret;
	char			*pwd;

	if ((ret = getenv("PWD")))
		return (ret);
	if (!(pwd = getcwd(NULL, 0)))
		ft_putendl_fd("getset_pwd_env: getcwd failed!", STDERR_FILENO);
	ret = set_env_var(NULL, "PWD", pwd);
	ft_strdel(&pwd);
	return (ret);
}

static void	set_shlvl(void)
{
	char	*lvlstr;
	int		lvln;

	if (!(lvlstr = getenv("SHLVL")))
	{
		set_env_var_n(NULL, "SHLVL", 1);
		return ;
	}
	lvln = 0;
	ft_secatoi(&lvln, lvlstr);
	lvln++;
	set_env_var_n(NULL, "SHLVL", lvln);
}

int			main(int ac, char **av)
{
	extern char	**environ;
	extern char **g_lvars;
	int			exval;

	switch_traps(TRUE);
	environ = ft_tabdup(environ);
	g_lvars = ft_tabnew();
	set_env_var(NULL, "SHELL", av[0]);
	set_shlvl();
	getset_pwd_env();
	if (!getenv("PATH"))
		set_env_var(NULL, "PATH", SH_DEFAULT_PATH);
	set_env_var(NULL, "_", av[0]);
	if (ac > 1 || !ft_isatty(STDIN_FILENO))
		exval = exec_shell((ac > 1) ? av[1] : NULL);
	else
		exval = interactive_shell();
	ft_tabfree(&g_lvars);
	return (exval);
}
