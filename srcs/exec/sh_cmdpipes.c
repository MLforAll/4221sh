/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmdpipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 01:55:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/26 02:43:51 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

void	exec_pipe(t_cmdnode *cmddat)
{
	if (cmddat->stdin_fd != -1)
	{
		close(STDIN_FILENO);
		dup2(cmddat->stdin_fd, STDIN_FILENO);
	}
	if (cmddat->stdout_fd != -1)
	{
		close(cmddat->pfd[0]);
		close(STDOUT_FILENO);
		dup2(cmddat->stdout_fd, STDOUT_FILENO);
	}
}

void	exec_pipe_clean(t_cmdnode *cmddat)
{
	if (!cmddat)
		return ;
	if (cmddat->stdin_fd != -1)
		close(cmddat->pfd[0]);
	if (cmddat->stdout_fd != -1)
		close(cmddat->pfd[1]);
}
