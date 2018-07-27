/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_evaluators.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 22:22:21 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/27 06:21:20 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "sh.h"

t_cmdnode	*eval_pipe(t_cmdnode *a, t_cmdnode *b, t_tab *pids)
{
	int		pfd[2];
	pid_t	pid;

	if (!a || !b)
		return (NULL);
	if (pipe(pfd) == -1)
		return (NULL);
	a->stdout_fd = pfd[1];
	(void)ft_memcpy(a->pfd, pfd, sizeof(pfd));
	b->stdin_fd = pfd[0];
	(void)ft_memcpy(b->pfd, pfd, sizeof(pfd));
	(void)exec_cmd(a, YES, &pid, NULL);
	(void)ft_ttabcat(pids, &pid, 1);
	return (b);
}

t_cmdnode	*eval_semi(t_cmdnode *a, t_cmdnode *b)
{
	if (!b)
		return (a);
	(void)exec_cmd(a, NO, NULL, NULL);
	return (b);
}

t_cmdnode	*eval_andif(t_cmdnode *a, t_cmdnode *b)
{
	if (exec_cmd(a, NO, NULL, NULL) == 0)
		return (b);
	return (NULL);
}

t_cmdnode	*eval_orif(t_cmdnode *a, t_cmdnode *b)
{
	if (exec_cmd(a, NO, NULL, NULL) != 0)
		return (b);
	return (NULL);
}

t_cmdnode	*eval_background(t_cmdnode *a, t_cmdnode *b)
{
	(void)exec_cmd(a, YES, NULL, NULL);
	return (b);
}
