/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd_bltnutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 16:17:07 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/03 01:31:34 by kdumarai         ###   ########.fr       */
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

static void			chg_ret(char **ret, char **last, char *path,
							unsigned int idx)
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
** get_newpath
**
** char *curr -> pwd
** char *path -> cd's argument
*/

char				*get_newpath(char *curr, char *path)
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
** getset_pwd_env -> get PWD from env (and set it if needed)
*/

char				*getset_pwd_env(void)
{
	char			*ret;
	char			*pwd;

	if ((ret = getenv("PWD")))
		return (ret);
	if (!(pwd = getcwd(NULL, 0)))
	{
		ft_putendl_fd("getset_pwd_env: getcwd() failed!", STDERR_FILENO);
		return (NULL);
	}
	ret = set_env_var(NULL, "PWD", pwd);
	ft_strdel(&pwd);
	return (ret);
}
