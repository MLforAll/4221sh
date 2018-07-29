/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 13:40:24 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/29 13:41:48 by kdumarai         ###   ########.fr       */
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
