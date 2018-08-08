/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_evaluators.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 22:22:21 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/08 22:10:10 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "sh.h"

/*
** How-to pipe
** -----------
**
** First, we create a pipe using the pipe(2) syscall.
** Then, we copy the fd refs (int cpy) for later use by exec_cmd().
** We copy the fd array to both `a' and `b' cmd nodes.
** However, it's only copied in `a' only when its stdin is not set.
** Because otherwise, the wrong pipe will be closed at exec time, due
** to the way the evaluator works.
*/

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
	if (a->stdin_fd == -1)
		(void)ft_memcpy(a->pfd, pfd, sizeof(pfd));
	(void)ft_memcpy(b->pfd, pfd, sizeof(pfd));
	a->stdout_fd = pfd[1];
	b->stdin_fd = pfd[0];
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
