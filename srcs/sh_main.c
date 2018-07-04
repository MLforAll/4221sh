/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/04 02:22:08 by kdumarai         ###   ########.fr       */
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
	g_sh_name = av[0];
	environ = ft_tabdup(environ);
	g_lvars = ft_tabnew();
	(void)set_env_var(NULL, "SHELL", av[0]);
	set_shlvl();
	(void)set_lvar_n("?", 0);
	getset_pwd_env();
	if (!getenv("PATH"))
		(void)set_env_var(NULL, "PATH", SH_DEFAULT_PATH);
	(void)set_env_var(NULL, "_", av[0]);
	if (ac > 1 || !ft_isatty(STDIN_FILENO))
		exval = exec_shell((ac > 1) ? av[1] : NULL);
	else
		exval = interactive_shell();
	ft_tabfree(&g_lvars);
	return (exval);
}
