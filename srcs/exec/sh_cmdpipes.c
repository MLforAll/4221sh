/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmdpipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 01:55:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/28 21:52:52 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

/*
** todo: maybe rm those useless close() calls
*/

void	exec_pipe(t_cmdnode *cmddat)
{
	if (cmddat->stdin_fd != -1)
	{
		(void)close(STDIN_FILENO);
		(void)dup2(cmddat->stdin_fd, STDIN_FILENO);
	}
	if (cmddat->stdout_fd != -1)
	{
		(void)close(cmddat->pfd[0]);
		(void)close(STDOUT_FILENO);
		(void)dup2(cmddat->stdout_fd, STDOUT_FILENO);
	}
}

/*
**void	exec_pipe_clean(t_cmdnode *cmddat)
**{
**	if (!cmddat)
**		return ;
**	if (cmddat->stdin_fd != -1)
**		(void)close(cmddat->pfd[0]);
**	if (cmddat->stdout_fd != -1)
**		(void)close(cmddat->pfd[1]);
**}
*/
