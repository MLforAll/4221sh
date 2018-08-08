/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmdpipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 01:55:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/08 05:59:02 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

inline void	exec_pipe(t_cmdnode *cmddat)
{
	if (cmddat->stdin_fd != -1)
	{
		(void)close(cmddat->pfd[1]);
		(void)dup2(cmddat->stdin_fd, STDIN_FILENO);
	}
	if (cmddat->stdout_fd != -1)
	{
		(void)close(cmddat->pfd[0]);
		(void)dup2(cmddat->stdout_fd, STDOUT_FILENO);
	}
}

inline void	clean_pipe(t_cmdnode *cmddat)
{
	if (cmddat->stdin_fd == -1)
		return ;
	(void)close(cmddat->pfd[0]);
	(void)close(cmddat->pfd[1]);
}
