/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/06 05:51:03 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"

/*
** main() of the shell
** -------------------
**
** Please do not add anything to this file
** Test program do not link it so they can use the other
** funcions without getting duplicate symbol error from the linker
**
** Only exception: static (private to this file) functions or data
*/

int			main(int ac, char **av)
{
	extern char	**environ;
	extern char **g_lvars;
	char		**env_bak;
	int			exval;

	g_sh_name = av[0];
	env_bak = environ;
	if (!(environ = ft_tabdup(environ)) || !shell_init(av))
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
