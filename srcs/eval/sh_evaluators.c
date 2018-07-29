/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_evaluators.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 22:22:21 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/28 23:53:30 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "sh.h"

t_cmdnode	*eval_pipe(t_btree *node, t_tab *pids)
{
	t_cmdnode	*a;
	t_cmdnode	*b;
	int			pfd[2];
	pid_t		pid;

	a = eval_ast(node->left, pids);
	b = eval_ast(node->right, pids);
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

t_cmdnode	*eval_semi(t_btree *node, t_tab *pids)
{
	t_cmdnode	*a;

	a = eval_ast(node->left, pids);
	(void)exec_cmd(a, NO, NULL, NULL);
	return (eval_ast(node->right, pids));
}

t_cmdnode	*eval_andif(t_btree *node, t_tab *pids)
{
	t_cmdnode	*a;

	a = eval_ast(node->left, pids);
	if (exec_cmd(a, NO, NULL, NULL) == 0)
		return (eval_ast(node->right, pids));
	return (NULL);
}

t_cmdnode	*eval_orif(t_btree *node, t_tab *pids)
{
	t_cmdnode	*a;

	a = eval_ast(node->left, pids);
	if (exec_cmd(a, NO, NULL, NULL) != 0)
		return (eval_ast(node->right, pids));
	return (NULL);
}

t_cmdnode	*eval_background(t_btree *node, t_tab *pids)
{
	t_cmdnode	*a;

	a = eval_ast(node->left, pids);
	(void)exec_cmd(a, YES, NULL, NULL);
	return (eval_ast(node->right, pids));
}
