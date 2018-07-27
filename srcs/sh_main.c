/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/27 06:19:07 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"

static void	set_shlvl(void)
{
	char	*lvlstr;
	int		lvln;

	if (!(lvlstr = getenv("SHLVL")))
	{
		(void)set_env_var_n(NULL, "SHLVL", 1);
		return ;
	}
	lvln = 0;
	if (!ft_secatoi(&lvln, lvlstr))
		sh_err(SH_ERR_INVID, "set_shlvl()", lvlstr);
	lvln++;
	(void)set_env_var_n(NULL, "SHLVL", lvln);
}

static void	shell_init(char **av)
{
	(void)set_env_var(NULL, "SHELL", av[0]);
	set_shlvl();
	(void)set_lvar_n("?", 0);
	getset_pwd_env();
	if (!getenv("PATH"))
		(void)set_env_var(NULL, "PATH", SH_DEFAULT_PATH);
	(void)set_env_var(NULL, "_", av[0]);
}

int			main(int ac, char **av)
{
	extern char	**environ;
	extern char **g_lvars;
	char		**env_bak;
	int			exval;

	switch_traps(TRUE);
	g_sh_name = av[0];
	env_bak = environ;
	if (!(environ = ft_tabdup(environ)) || !(g_lvars = ft_tabnew()))
		return (sh_err_ret(SH_ERR_MALLOC, NULL, NULL, EXIT_FAILURE));
	shell_init(av);
	if (ac > 1 || !ft_isatty(STDIN_FILENO))
		exval = exec_shell((ac > 1) ? av[1] : NULL);
	else
		exval = interactive_shell();
	ft_tabfree(&g_lvars);
	ft_tabfree(&environ);
	sh_jobs_rmall();
	environ = env_bak;
	return (exval);
}
