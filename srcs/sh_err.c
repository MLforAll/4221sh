/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 21:23:18 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/01 15:15:52 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/param.h>
#include "sh.h"

void					sh_err(t_errs errc, const char *bltn, const char *path)
{
	const char		*errs[] = {
		"Undefined error", "command not found", "No such file or directory",
		"Can't cd to directory", "not set", "too many arguments",
		"Permission denied", "fork(): Out of resource",
		"Too many symbolic links", "Not a directory",
		"numeric argument required", "not a valid identifier",
		"argument required", "no such job", "Bad file descriptor",
		"malloc() failure", "Bad file", "Fatal error", "Undefined error"};

	ft_putstrsec_fd(g_sh_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (bltn)
	{
		ft_putstr_fd(bltn, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (path)
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd((errc == SH_ERR_NOSET) ? " " : ": ", STDERR_FILENO);
	}
	if (errc < SH_ERR_MAX)
		ft_putendl_fd(errs[errc], STDERR_FILENO);
}

inline int				sh_err_ret(t_errs errc,
									const char *bltn,
									const char *path,
									int rvl)
{
	sh_err(errc, bltn, path);
	return (rvl);
}

static inline t_uint8	can_read_link(char **chk, struct stat *st)
{
	char	*tmp;

	if (!(tmp = ft_strnew(st->st_size)))
	{
		ft_strdel(chk);
		return (FALSE);
	}
	if (readlink(*chk, tmp, st->st_size) == -1)
	{
		ft_strdel(chk);
		free(tmp);
		return (FALSE);
	}
	free(*chk);
	*chk = tmp;
	return (TRUE);
}

static t_uint8			check_too_much_links(const char *path)
{
	struct stat	st;
	int			n;
	char		*chk;

	n = MAXSYMLINKS;
	if (!(chk = ft_strdup(path)))
		return (FALSE);
	while (n--)
	{
		if (lstat(chk, &st) == -1)
		{
			free(chk);
			return (FALSE);
		}
		if (!S_ISLNK(st.st_mode))
			break ;
		if (!can_read_link(&chk, &st))
			return (FALSE);
	}
	free(chk);
	return ((n > 0) ? FALSE : TRUE);
}

t_errs					get_errcode_for_path(const char *path,
											int mode,
											t_uint8 dir)
{
	struct stat	st;

	if (access(path, F_OK) == -1)
		return ((check_too_much_links(path)) ? SH_ERR_TMLNK : SH_ERR_NOENT);
	if (stat(path, &st) == -1)
		return (SH_ERR_UNDEFINED);
	if (dir && !S_ISDIR(st.st_mode))
		return (SH_ERR_NOTDIR);
	else if (!dir && !S_ISREG(st.st_mode))
		return (SH_ERR_NOENT);
	if (access(path, mode) == -1)
		return (SH_ERR_PERM);
	return (SH_ERR_UNDEFINED);
}
