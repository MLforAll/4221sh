/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_errfiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 21:23:18 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/03 02:34:35 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/param.h>
#include "sh.h"

static inline t_uint8	can_read_link(char **chk, struct stat *st)
{
	char	*tmp;

	if (!(tmp = ft_strnew((size_t)st->st_size)))
	{
		ft_strdel(chk);
		return (FALSE);
	}
	if (readlink(*chk, tmp, (size_t)st->st_size) == -1)
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

inline static t_errs	get_errcode_for_path_main(const char *ptr,
												int mode, t_uint8 dir)
{
	struct stat	st;

	if (stat(ptr, &st) == -1)
		return (SH_ERR_UNDEFINED);
	if (dir && !S_ISDIR(st.st_mode))
		return (SH_ERR_NOTDIR);
	else if (!dir && !S_ISREG(st.st_mode))
		return (SH_ERR_NOENT);
	if (access(ptr, mode) == -1)
		return (SH_ERR_PERM);
	return (SH_ERR_UNDEFINED);
}

t_errs					get_errcode_for_path(const char *path,
											int mode,
											t_uint8 dir, t_uint8 creatable)
{
	const char	*ptr;
	char		*mpath;
	t_errs		ret;

	if (access(path, F_OK) == -1)
	{
		if (!creatable)
			return ((check_too_much_links(path)) ? SH_ERR_TMLNK : SH_ERR_NOENT);
		mpath = get_basedir(path);
		ptr = mpath;
		dir = YES;
	}
	else
	{
		ptr = path;
		mpath = NULL;
	}
	ret = get_errcode_for_path_main(ptr, mode, dir);
	free(mpath);
	return (ret);
}
