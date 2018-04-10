/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 18:31:09 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/10 20:00:58 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "sh.h"

int			free_return(void **data, int retv)
{
	if (data && *data)
	{
		free(*data);
		*data = NULL;
	}
	return (retv);
}

void		switch_traps(int ign)
{
	void	(*act)(int);

	act = (ign) ? SIG_IGN : SIG_DFL;
	signal(SIGINT, act);
	signal(SIGTERM, act);
	signal(SIGTSTP, act);
}

static void	dup_out_to_pipe(int outfd, int pfd)
{
	if (pfd < 3)
		return ;
	close(outfd);
	dup2(pfd, outfd);
}

void		prepare_dups(t_cmd *cmd)
{
	if (cmd->c_pfd[0] < 3 || cmd->c_pfd[1] < 3)
		return ;
	if (!cmd->prev)
		close(cmd->c_pfd[0]);
	else
		dup_out_to_pipe(STDIN_FILENO, cmd->prev->c_pfd[0]);
	if (cmd->next)
		dup_out_to_pipe(STDOUT_FILENO, cmd->c_pfd[1]);
	else
		close(cmd->c_pfd[1]);
}
