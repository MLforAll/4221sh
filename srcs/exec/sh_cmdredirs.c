/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmdredirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:42:44 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/04 02:12:39 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "sh.h"

static void			do_redir_action(t_redirect *redir, int oflags)
{
	int		fd;

	close(redir->io_nbr);
	if ((fd = open(redir->filename, oflags, 0644)) != redir->io_nbr)
	{
		dup2(fd, redir->io_nbr);
		close(fd);
	}
}

static void			do_agreg(t_redirect *redir)
{
	char	*n_str;

	if (redir->agreg == -1)
	{
		close(redir->io_nbr);
		return ;
	}
	if (dup2(redir->agreg, redir->io_nbr) == -1)
	{
		if (!(n_str = ft_itoa(redir->agreg)))
			sh_err(SH_ERR_MALLOC, NULL, NULL);
		sh_err(SH_ERR_BADFD, NULL, n_str);
		free(n_str);
		exit(1);
	}
}

static void			do_str_to_stdin(t_redirect *redir, t_cmdnode *cmddat)
{
	int		cfd[2];
	char	buff[32];
	ssize_t	rb;

	pipe(cfd);
	if (cmddat->stdin_fd != -1)
		while ((rb = read(redir->io_nbr, buff, 32)) > 0)
			write(cfd[1], buff, rb);
	ft_putstr_fd(redir->filename, cfd[1]);
	close(redir->io_nbr);
	dup2(cfd[0], redir->io_nbr);
	close(cfd[1]);
}

inline static void	save_fd(t_tab *bakptr, int fd_to_save)
{
	t_bakfds	bak;

	bak.orig = fd_to_save;
	bak.bak = dup(fd_to_save);
	ft_ttabcat(bakptr, &bak, 1);
}

void				exec_redir(t_cmdnode *cmddat, t_tab *bakptr)
{
	t_list		*bw;
	t_redirect	*redir;

	bw = cmddat->c_redirects;
	while (bw)
	{
		redir = (t_redirect*)bw->content;
		if (bakptr)
			save_fd(bakptr, redir->io_nbr);
		if (redir->rtype == GREAT || redir->rtype == LESS)
		{
			if (redir->filename)
				do_redir_action(redir, (redir->rtype == LESS)
									? O_RDONLY : O_WRONLY | O_CREAT | O_TRUNC);
			else
				do_agreg(redir);
		}
		else if (redir->rtype == DGREAT)
			do_redir_action(redir, O_WRONLY | O_CREAT | O_APPEND);
		else if (redir->rtype == DLESS)
			do_str_to_stdin(redir, cmddat);
		bw = bw->next;
	}
}
