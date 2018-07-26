/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd_bltncmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:26:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/27 00:03:15 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

/*
** get_cd_path (static)
**
** int idx   -> ac counter
** int opts  -> opts bitwise-OR
** char **av
** char *pwd
*/

static char			*get_cd_path(int idx, int opts, char **av, char *pwd)
{
	char			*ret;
	char			*oldpwd;

	if (opts & CD_DASH_OPT)
	{
		if (!(oldpwd = getenv("OLDPWD")))
			sh_err(SH_ERR_NOSET, av[0], "OLDPWD");
		return ((oldpwd) ? ft_strdup(oldpwd) : NULL);
	}
	if (!av[idx])
	{
		if (!(ret = getenv("HOME")))
			sh_err(SH_ERR_NOSET, av[0], "HOME");
		return ((ret) ? ft_strdup(ret) : NULL);
	}
	if (!(opts & CD_P_OPT))
		return (get_newpath(pwd, av[idx]));
	return (ft_strdup(av[idx]));
}

/*
** cd_usage (static)
**
** char a -> error character
*/

static int			cd_usage(char a)
{
	ft_putstr_fd("cd: illegal option -- ", STDERR_FILENO);
	ft_putchar_fd(a, STDERR_FILENO);
	ft_putendl_fd("\nusage: [-L|-P] [dir]", STDERR_FILENO);
	return (EXIT_FAILURE);
}

/*
** cd_set_env (inline static) -> set PWD and OLDPWD env vars
** char *pwd
** char *path_cd              -> path to cd to
** int cd_opts                -> cd user options (switches)
*/

inline static void	cd_set_env(char *pwd, char **path_cd, int cd_opts)
{
	(void)set_env_var(NULL, "OLDPWD", pwd);
	if (cd_opts & CD_P_OPT)
	{
		ft_strdel(path_cd);
		*path_cd = getcwd(NULL, 0);
	}
	(void)set_env_var(NULL, "PWD", *path_cd);
}

/*
** cd_bltn
**
** int ac
** char	**av
*/

int					cd_bltn(int ac, char **av)
{
	char			*path_cd;
	char			*pwd;
	int				cd_opts;
	int				idx;

	(void)ac;
	pwd = getset_pwd_env();
	idx = 1;
	if ((cd_opts = ft_args_opts(av, &idx, "PL\004", "PL")) < 0)
		return (cd_usage(-cd_opts));
	if (!(path_cd = get_cd_path(idx, cd_opts, av, pwd)))
		return (EXIT_FAILURE);
	if (chdir(path_cd) == -1)
	{
		sh_err(get_errcode_for_path(path_cd, X_OK, YES), av[0], path_cd);
		return (free_return((void**)&path_cd, EXIT_FAILURE));
	}
	(cd_opts & CD_DASH_OPT) ? ft_putendl(path_cd) : 0;
	cd_set_env(pwd, &path_cd, cd_opts);
	ft_strdel(&path_cd);
	return (EXIT_SUCCESS);
}
