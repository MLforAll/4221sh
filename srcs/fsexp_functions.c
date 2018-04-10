/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsexp_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 21:26:34 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/10 20:00:38 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "sh.h"

char		*get_basedir(const char *f_path)
{
	char			*ret;
	char			*rchr_ret;
	size_t			ret_len;

	if (!f_path)
		return (NULL);
	if (!(rchr_ret = ft_strrchr(f_path, '/')))
		return (ft_strdup("."));
	if ((ret_len = rchr_ret - f_path) == 0)
		ret_len = 1;
	if (!(ret = ft_strnew(ret_len)))
		return (NULL);
	ft_strncpy(ret, f_path, ret_len);
	return (ret);
}

static char	*get_elem_path(const char *d_path, char *name)
{
	char			*ret;

	if (!d_path || !name)
		return (NULL);
	if (!(ret = ft_strnew(ft_strlen(d_path) + ft_strlen(name) + 1)))
		return (NULL);
	ft_strcat(ret, d_path);
	ft_strcat(ret, "/");
	ft_strcat(ret, name);
	return (ret);
}

char		*search_dir_for_file(const char *d_path, const char *name)
{
	DIR				*dirp;
	struct dirent	*dird;
	char			*elem_path;

	if (!d_path || !name || !(dirp = opendir(d_path)))
		return (NULL);
	elem_path = NULL;
	while ((dird = readdir(dirp)))
	{
		elem_path = get_elem_path(d_path, dird->d_name);
		if (ft_strcmp(dird->d_name, name) == 0 && dird->d_type != DT_DIR)
			break ;
		ft_strdel(&elem_path);
	}
	closedir(dirp);
	return (elem_path);
}

static int	is_exec(const char *d_path, char *name, int folder)
{
	struct stat		st;
	char			*elem_path;
	int				ret;

	if (!d_path || !name || !(elem_path = get_elem_path(d_path, name)))
		return (FALSE);
	ret = FALSE;
	if (stat(elem_path, &st) != -1 && (st.st_mode & S_IXUSR
		|| st.st_mode & S_IXGRP || st.st_mode & S_IXOTH)
		&& S_ISDIR(st.st_mode) == folder)
		ret = TRUE;
	ft_strdel(&elem_path);
	return (ret);
}

t_list		*search_files_begin(const char *f_path, const char *s_dir, int exec)
{
	t_list			*ret;
	DIR				*dirp;
	struct dirent	*dird;
	char			*basedir;
	char			*name;

	basedir = (!s_dir) ? get_basedir(f_path) : (char*)s_dir;
	name = get_name_from_path(f_path);
	dirp = opendir(basedir);
	ret = NULL;
	while (dirp && (dird = readdir(dirp)))
	{
		if ((!exec && ft_strstart(dird->d_name, name))
			|| (exec && ft_strstart(dird->d_name, name)
				&& is_exec(s_dir, dird->d_name, FALSE)))
		{
			ft_lstadd(&ret, ft_lstnew(dird->d_name, dird->d_namlen + 1));
			ret->content_size = (size_t)dird->d_type;
		}
	}
	if (dirp)
		closedir(dirp);
	if (!s_dir)
		ft_strdel(&basedir);
	return (ret);
}
