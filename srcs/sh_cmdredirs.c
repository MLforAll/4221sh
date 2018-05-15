/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmdredirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:42:44 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/15 03:06:53 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "sh.h"

static void	do_redir_action(t_redirect *redir, int oflags)
{
	int		fd;

	close(redir->io_nbr);
	fd = open(redir->filename, oflags, 0644);
	if (fd != redir->io_nbr)
	{
		dup2(fd, redir->io_nbr);
		close(fd);
	}
}

static void	do_agreg(t_redirect *redir)
{
	close(redir->io_nbr);
	if (redir->agreg == -1)
		return ;
	dup2(redir->agreg, redir->io_nbr);
}

void		exec_redir(t_cmdnode *cmddat)
{
	t_list		*bw;
	t_redirect	*redir;

	bw = cmddat->c_redirects;
	while (bw)
	{
		redir = (t_redirect*)bw->content;
		if (redir->rtype == GREAT)
		{
			if (redir->filename)
				do_redir_action(redir, O_WRONLY | O_CREAT | O_TRUNC);
			else
				do_agreg(redir);
		}
		if (redir->rtype == DGREAT)
			do_redir_action(redir, O_WRONLY | O_CREAT | O_APPEND);
		if (redir->rtype == LESS)
			do_redir_action(redir, O_RDONLY);
		bw = bw->next;
	}
}
