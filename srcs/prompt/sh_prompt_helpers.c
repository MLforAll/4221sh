/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prompt_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 21:41:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/09 19:04:45 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/param.h>
#include <pwd.h>
#include <stdlib.h>
#include "sh.h"

int			add_username(char **dest)
{
	struct passwd	pwdat;
	struct passwd	*ppw;
	char			*buff;
	long			charbufflen;
	int				status;

	if (!dest)
		return (FALSE);
	buff = NULL;
	if (!(ppw = getpwuid(getuid()))
		&& ((charbufflen = sysconf(_SC_GETPW_R_SIZE_MAX)) == -1
			|| !(buff = ft_strnew(charbufflen))
			|| getpwuid_r(getuid(), &pwdat, buff, (size_t)charbufflen, &ppw)))
	{
		free(buff);
		return (FALSE);
	}
	status = (ppw && ft_stradd(dest, ppw->pw_name));
	free(buff);
	return (status);
}

int			add_hostname(char **dest)
{
	char			hostname[MAXHOSTNAMELEN + 1];
	char			*dot;
	int				status;

	if (gethostname(hostname, MAXHOSTNAMELEN) == -1)
		return (FALSE);
	if ((dot = ft_strchr(hostname, '.')))
		status = ft_strnadd(dest, hostname, (size_t)(dot - hostname));
	else
		status = ft_stradd(dest, hostname);
	return (status);
}

static char	*build_home(char *pwd)
{
	char			*ret;
	char			*home;
	const char		*stret;

	if (!pwd || !(home = get_env_var(NULL, "HOME")))
		return (NULL);
	if ((stret = ft_strstart(pwd, home)))
		ret = ft_strdup("~");
	else
		ret = ft_strnew(0);
	if (!ret)
		return (NULL);
	if (!ft_stradd(&ret, (stret) ? stret : pwd))
		ft_strdel(&ret);
	return (ret);
}

int			add_pwd(char **dest, int all)
{
	char			*path;
	char			*pwd;
	char			*tmp;

	tmp = NULL;
	if (!(pwd = get_env_var(NULL, "PWD")))
	{
		if (!(tmp = getcwd(NULL, 0)))
			return (FALSE);
		path = tmp;
	}
	else if (!(path = build_home(pwd)))
		return (FALSE);
	if (!all)
	{
		tmp = path;
		path = get_name_from_path_2(path);
		ft_strdel(&tmp);
	}
	(void)ft_stradd(dest, path);
	ft_strdel(&path);
	return (TRUE);
}
