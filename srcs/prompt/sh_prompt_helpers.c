/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prompt_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 21:41:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/01 19:13:50 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/param.h>
#include <pwd.h>
#include <stdlib.h>
#include "sh.h"

int			add_username(char **dest)
{
	uid_t			puid;
	struct passwd	*ppw;

	if (!dest || !(puid = getuid()))
		return (FALSE);
	if (!(ppw = getpwuid(puid)))
		return (FALSE);
	ft_stradd(dest, ppw->pw_name);
	return (TRUE);
}

int			add_hostname(char **dest)
{
	char			hostname[MAXHOSTNAMELEN + 1];
	char			*dot;

	if (gethostname(hostname, MAXHOSTNAMELEN) == -1)
		return (FALSE);
	if ((dot = ft_strchr(hostname, '.')))
		ft_strnadd(dest, hostname, (size_t)(dot - hostname));
	else
		ft_stradd(dest, hostname);
	return (TRUE);
}

static char	*build_home(char *pwd)
{
	char			*ret;
	char			*home;
	const char		*stret;

	if (!pwd || !(home = getenv("HOME")))
		return (NULL);
	if ((stret = ft_strstart(pwd, home)))
		ret = ft_strdup("~");
	else
		ret = ft_strnew(0);
	if (!ret)
		return (NULL);
	ft_stradd(&ret, (stret) ? stret : pwd);
	return (ret);
}

int			add_pwd(char **dest, int all)
{
	char			*path;
	char			*pwd;
	char			*tmp;

	tmp = NULL;
	if (!(pwd = getenv("PWD")))
	{
		if (!(tmp = getcwd(NULL, 0)))
			return (FALSE);
		path = tmp;
	}
	else
	{
		if (!(path = build_home(pwd)))
			return (FALSE);
	}
	if (!all)
	{
		tmp = path;
		path = get_name_from_path_2(path);
		ft_strdel(&tmp);
	}
	ft_stradd(dest, path);
	ft_strdel(&path);
	return (TRUE);
}
