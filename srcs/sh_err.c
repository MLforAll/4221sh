/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 21:23:18 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/03 02:34:33 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
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
