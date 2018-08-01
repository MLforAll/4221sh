/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_eshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 02:41:29 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/01 19:08:45 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "sh.h"

static t_uint8	is_file_binary(const char *path)
{
	int			fd;
	char		buff[512];
	ssize_t		rb;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (FALSE);
	while ((rb = read(fd, buff, 512)) > 0)
	{
		if (ft_memchr(buff, '\0', (size_t)rb))
		{
			(void)close(fd);
			return (FALSE);
		}
	}
	(void)close(fd);
	return (rb != -1);
}

int				exec_shell(const char *path)
{
	char		*line;
	int			fd;
	int			ret;
	int			tmp;

	if (!is_file_binary(path))
		return (sh_err_ret(SH_ERR_BADFILE, NULL, path, EXIT_FAILURE));
	if ((fd = (!path) ? STDIN_FILENO : open(path, O_RDONLY)) == -1)
		return (EXIT_FAILURE);
	ret = EXIT_SUCCESS;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if ((tmp = eval_line(&line, fd)) != -1)
		{
			ret = tmp;
			(void)set_lvar_n("?", ret);
		}
		ft_strdel(&line);
	}
	if (fd != STDIN_FILENO)
		(void)close(fd);
	return (ret);
}
