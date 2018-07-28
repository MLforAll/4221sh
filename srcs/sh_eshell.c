/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_eshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 02:41:29 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/28 15:13:38 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "sh.h"

int			exec_shell(const char *path)
{
	char		*line;
	int			fd;
	int			ret;
	int			tmp;

	fd = (!path) ? STDIN_FILENO : open(path, O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	ret = EXIT_SUCCESS;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if ((tmp = eval_line(&line, NO)) != -1)
		{
			ret = tmp;
			(void)set_lvar_n("?", ret);
		}
		ft_strdel(&line);
	}
	if (fd != STDIN_FILENO)
		close(fd);
	return (ret);
}
