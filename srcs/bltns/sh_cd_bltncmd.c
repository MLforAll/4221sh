/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd_bltncmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:26:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/20 03:59:25 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

char			*getset_pwd_env(void)
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

/*
** path = argv of cd (e.g cd misc => misc is path)
*/

static void		chg_ret(char **ret, char **last, char *path, unsigned int idx)
{
	char			*rchr;
	char			*tmp;
	size_t			sublen;

	if (!ret || !last || !*last)
		return ;
	if (!path)
	{
		if (*ret && (rchr = ft_strrchr(*ret, '/')))
		{
			sublen = (rchr - *ret <= 0) ? 1 : rchr - *ret;
			if (!(tmp = ft_strsub(*ret, 0, sublen)))
				return ;
			ft_strdel(ret);
			*ret = tmp;
		}
		*last += ((*last)[2] != '\0') + 2;
		return ;
	}
	if ((**last && *last != path) || (*path == '/' && !**ret))
		ft_stradd(ret, "/");
	ft_strnadd(ret, *last, idx);
}

static char		*get_newpath(char *curr, char *path)
{
	char			*ret;
	char			*last;
	unsigned int	idx;

	if (!path || !(ret = ft_strdup((!curr || *curr == '/') ? "" : curr)))
		return (NULL);
	last = path + (*path == '/');
	idx = 0;
	while (last[idx])
	{
		if (idx == 0 && ft_strncmp(last, ".", ft_strclen(last, '/')) == 0)
			last += (last[1] != '\0') + 1;
		else if (idx == 0 && ft_strncmp(last, "..", ft_strclen(last, '/')) == 0)
			chg_ret(&ret, &last, NULL, idx);
		else if (last[idx] == '/')
		{
			chg_ret(&ret, &last, path, idx);
			last = &last[idx + 1];
			idx = 0;
		}
		else
			idx++;
	}
	chg_ret(&ret, &last, path, idx);
	return (ret);
}

static char		*get_cd_path(int idx, int opts, char **av, char *pwd)
{
	char			*ret;
	char			*oldpwd;

	if (opts & CD_DASH_OPT)
	{
		if (!(oldpwd = getenv("OLDPWD")))
			sh_err(SH_ERR_NOSET, av[0], "OLDPWD");
		return (ft_strdup(oldpwd));
	}
	if (!av[idx])
	{
		if (!(ret = getenv("HOME")))
			sh_err(SH_ERR_NOSET, av[0], "HOME");
		return (ft_strdup(ret));
	}
	if (!(opts & CD_P_OPT))
		return (get_newpath(pwd, av[idx]));
	return (ft_strdup(av[idx]));
}

int				cd_bltn(int ac, char **av, int outfd)
{
	char			*path_cd;
	char			*pwd;
	int				cd_opts;
	int				idx;

	pwd = getset_pwd_env();
	idx = 1;
	cd_opts = get_bltn_opts(ac, av, &idx, "PL\004");
	if (!(path_cd = get_cd_path(idx, cd_opts, av, pwd)))
		return (EXIT_FAILURE);
	if (chdir(path_cd) == -1)
	{
		sh_err(get_errcode_for_path(path_cd, X_OK, YES), av[0], path_cd);
		return (free_return((void**)&path_cd, EXIT_FAILURE));
	}
	(cd_opts & CD_DASH_OPT) ? ft_putendl_fd(path_cd, outfd) : 0;
	set_env_var(NULL, "OLDPWD", pwd);
	if (cd_opts & 0x1)
	{
		ft_strdel(&path_cd);
		path_cd = getcwd(NULL, 0);
	}
	set_env_var(NULL, "PWD", path_cd);
	ft_strdel(&path_cd);
	return (EXIT_SUCCESS);
}
