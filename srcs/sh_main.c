/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/29 06:32:28 by kdumarai         ###   ########.fr       */
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

t_uint8		shell_init(void)
{
	extern char **g_lvars;

	switch_traps(TRUE);
	if (g_lvars)
		ft_tabfree(&g_lvars);
	if (!(g_lvars = ft_tabnew()))
		return (FALSE);
	sh_jobs_rmall();
	set_shlvl();
	(void)set_lvar_n("?", 0);
	getset_pwd_env();
	if (!getenv("PATH"))
		(void)set_env_var(NULL, "PATH", SH_DEFAULT_PATH);
	(void)set_env_var(NULL, "_", g_sh_name);
	return (TRUE);
}

int			main(int ac, char **av)
{
	extern char	**environ;
	extern char **g_lvars;
	char		**env_bak;
	int			exval;

	g_sh_name = av[0];
	env_bak = environ;
	if (!(environ = ft_tabdup(environ)) || !shell_init())
		return (sh_err_ret(SH_ERR_MALLOC, NULL, NULL, EXIT_FAILURE));
	(void)set_env_var(NULL, "SHELL", g_sh_name);
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
