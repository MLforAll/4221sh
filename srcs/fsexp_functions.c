/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsexp_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 21:26:34 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/29 00:37:59 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "sh.h"

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
