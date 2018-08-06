/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmdredirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:42:44 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/06 22:53:14 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "sh.h"

static t_uint8		do_redir_action(t_redirect *redir,
									int oflags,
									t_uint8 writable)
{
	int			fd;
	int			fdchk;
	t_errs		err;

	fdchk = (redir->io_nbr == -2) ? STDOUT_FILENO : redir->io_nbr;
	if ((fd = open(redir->data, oflags, 0644)) == -1)
	{
		err = get_errcode_for_path(redir->data,
				(writable) ? W_OK : R_OK, NO, writable);
		sh_err(err, NULL, redir->data);
		return (FALSE);
	}
	(void)dup2(fd, fdchk);
	(void)close(fd);
	if (redir->io_nbr == -2)
		(void)dup2(STDOUT_FILENO, STDERR_FILENO);
	return (TRUE);
}

static t_uint8		do_agreg(t_redirect *redir)
{
	char	*n_str;
	int		errfd;

	if (redir->agreg == -1)
	{
		(void)close(redir->io_nbr);
		return (TRUE);
	}
	if (dup2(redir->agreg, redir->io_nbr) == -1)
	{
		if ((errfd = dup(redir->agreg)) == -1)
			errfd = redir->agreg;
		else
		{
			(void)close(errfd);
			errfd = redir->io_nbr;
		}
		if (!(n_str = ft_itoa(errfd)))
			sh_err(SH_ERR_MALLOC, NULL, NULL);
		sh_err(SH_ERR_BADFD, NULL, n_str);
		free(n_str);
		return (FALSE);
	}
	return (TRUE);
}

static void			do_str_to_stdin(t_redirect *redir, t_cmdnode *cmddat)
{
	int		cfd[2];
	char	buff[32];
	ssize_t	rb;

	if (pipe(cfd) == -1)
		return ;
	if (cmddat->stdin_fd != -1)
		while ((rb = read(redir->io_nbr, buff, 32)) > 0)
			(void)write(cfd[1], buff, (size_t)rb);
	ft_putstr_fd(redir->data, cfd[1]);
	(void)dup2(cfd[0], redir->io_nbr);
	(void)close(cfd[1]);
}

inline static void	save_fd(t_tab *bakptr, int fd_to_save)
{
	t_bakfds	bak;

	bak.orig = fd_to_save;
	bak.bak = dup(fd_to_save);
	ft_ttabcat(bakptr, &bak, 1);
}

int					exec_redir(t_cmdnode *cmddat, t_tab *bakptr)
{
	t_list		*bw;
	t_redirect	*redir;

	bw = cmddat->c_redirects;
	while (bw)
	{
		redir = (t_redirect*)bw->content;
		if (bakptr)
			save_fd(bakptr, redir->io_nbr);
		if ((redir->rtype == GREAT || redir->rtype == LESS)
			&& ((redir->data && !do_redir_action(redir, (redir->rtype == LESS)
							? O_RDONLY : O_WRONLY | O_CREAT | O_TRUNC,
							redir->rtype == GREAT))
				|| (!redir->data && !do_agreg(redir))))
			return (EXIT_FAILURE);
		else if (redir->rtype == DGREAT
			&& !do_redir_action(redir, O_WRONLY | O_CREAT | O_APPEND, YES))
			return (EXIT_FAILURE);
		else if (redir->rtype == DLESS)
			do_str_to_stdin(redir, cmddat);
		bw = bw->next;
	}
	return (EXIT_SUCCESS);
}
