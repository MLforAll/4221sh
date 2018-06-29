/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd_bltncmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:26:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/29 03:04:20 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

/*
** chg_ret (static)
**
** char **ret        -> ref of return value for get_newpath()
** char **last       -> ref of last var in get_newpath()
** char *path        -> cd's argument
** unsigned int idx  -> counter
*/

static void			chg_ret(char **ret, char **last, char *path, unsigned int idx)
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
	if (**last || (*path == '/' && !**ret))
		ft_stradd(ret, "/");
	ft_strnadd(ret, *last, idx);
}

/*
** get_newpath_init (static)
**
** char *curr -> pwd
** char *path -> cd's argument
*/

inline static char	*get_newpath_init(char *curr, char *path)
{
	if ((*path == '/' || !curr || ft_strequ(curr, "/")))
		return (ft_strdup(""));
	return (ft_strdup(curr));
}

/*
** get_newpath (static)
**
** char *curr -> pwd
** char *path -> cd's argument
*/

static char			*get_newpath(char *curr, char *path)
{
	char			*ret;
	char			*last;
	unsigned int	idx;

	if (!path || !(ret = get_newpath_init(curr, path)))
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
	(cd_opts & CD_DASH_OPT) ? ft_putendl(path_cd) : 0;
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
