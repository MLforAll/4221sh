/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 02:41:29 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/12 02:42:32 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "sh.h"

int			exec_shell(const char *path)
{
	char		*line;
	int			fd;
	int			ret;

	fd = (!path) ? STDIN_FILENO : open(path, O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	ret = EXIT_SUCCESS;
	while (get_next_line(fd, &line) > 0)
	{
		ret = exec_cmds(line);
		set_env_var_n(NULL, "?", ret);
		ft_strdel(&line);
	}
	if (fd != STDIN_FILENO)
		close(fd);
	return (ret);
}
