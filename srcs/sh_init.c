/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 13:40:24 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/08 05:51:41 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"

static void	set_shlvl(void)
{
	char	*lvlstr;
	int		lvln;

	if (!(lvlstr = get_env_var(NULL, "SHLVL")))
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

static void	set_av_vars(char **av)
{
	char	*n_str;
	int		idx;

	idx = 0;
	while (av[idx])
	{
		if ((n_str = ft_itoa(idx)))
		{
			(void)set_lvar(n_str, av[idx]);
			free(n_str);
		}
		idx++;
	}
	if ((n_str = ft_itoa(idx > 0 ? idx - 1 : 0)))
	{
		(void)set_lvar("#", n_str);
		free(n_str);
	}
}

t_uint8		shell_init(char **av)
{
	extern char **g_lvars;

	switch_traps(TRUE);
	if (g_lvars)
		ft_tabfree(&g_lvars);
	if (!(g_lvars = ft_tabnew()))
		return (FALSE);
	set_av_vars(av);
	sh_jobs_rmall();
	set_shlvl();
	(void)set_lvar_n("?", 0);
	getset_pwd_env();
	if (!get_env_var(NULL, "PATH"))
		(void)set_env_var(NULL, "PATH", SH_DEFAULT_PATH);
	(void)set_env_var(NULL, "_", g_sh_name);
	return (TRUE);
}
