/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 21:23:18 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/02 04:55:46 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/param.h>
#include "sh.h"

int			sh_err(int errc, const char *bltn, const char *path)
{
	const char		*errs[] = {
		"Undefined error", "command not found", "No such file or directory",
		"Can't cd to directory", "not set", "too many arguments",
		"Permission denied", "Fork failed", "Too many symbolic links",
		"Not a directory", "numeric argument required",
		"not a valid identifier", "argument required", "no such job",
		"Undefined error", NULL};

	ft_putstr_fd(SH_NAME, STDERR_FILENO);
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
	if (errc >= 0 && errc < SH_ERR_MAX)
		ft_putendl_fd(errs[errc], STDERR_FILENO);
	return (1);
}

int			sh_err_ret(int errc, const char *bltn, const char *path, int retv)
{
	sh_err(errc, bltn, path);
	return (retv);
}

void		sh_child_signaled(int sigc)
{
	const char	*errs[30] = {"Hangup", NULL, NULL, "Illegal instruction",
		"Trace/BPT trap", "Abort trap", "EMT trap", "Floating point exception",
		"Killed", "Bus error", "Segmentation fault",
		"Bad system call", NULL, "Alarm clock", "Terminated",
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, "Cputime limit exceeded",
		"Filesize limit exceeded", "Virtual timer expired",
		"Profiling timer expired", NULL, NULL,
		"User defined signal 1", "User defined signal 2"};

	if (sigc <= 0 || sigc > 31)
		return ;
	ft_putchar('\n');
	if (!errs[sigc - 1])
		return ;
	ft_putstr_fd(errs[sigc - 1], STDIN_FILENO);
	ft_putstr_fd(": ", STDIN_FILENO);
	ft_putnbr_fd(sigc, STDIN_FILENO);
	ft_putchar_fd('\n', STDIN_FILENO);
}

static int	check_too_much_links(const char *path)
{
	struct stat	st;
	int			n;
	char		*chk;
	char		*tmp;

	n = MAXSYMLINKS;
	chk = ft_strdup(path);
	while (n--)
	{
		if (lstat(chk, &st) == -1)
			return (free_return((void**)&chk, FALSE));
		if (!S_ISLNK(st.st_mode))
			break ;
		tmp = chk;
		if (!(chk = ft_strnew(st.st_size)))
			return (free_return((void**)&tmp, FALSE));
		if (readlink(tmp, chk, st.st_size) == -1)
			return (free_return((void**)&chk, FALSE));
		ft_strdel(&tmp);
	}
	ft_strdel(&chk);
	return ((n > 0) ? FALSE : TRUE);
}

int			get_errcode_for_path(const char *path, int mode, int dir)
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
