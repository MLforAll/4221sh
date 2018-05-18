/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_eval.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 22:22:21 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/19 01:47:49 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "sh.h"

static void			clean_pipes(pid_t *pids)
{
	while (*pids != -1)
	{
		if (*pids > 0 && waitpid(*pids, NULL, WNOHANG) == 0)
		{
			kill(*pids, SIGKILL);
			waitpid(*pids, NULL, 0);
			*pids = 0;
		}
		pids++;
	}
}

static t_cmdnode	*eval_pipe(t_cmdnode *a, t_cmdnode *b, pid_t *pids)
{
	int		pfd[2];

	pipe(pfd);
	a->stdout_fd = pfd[1];
	b->stdin_fd = pfd[0];
	exec_cmd(a, YES, pids, NULL);
	close(pfd[1]);
	return (b);
}

static t_cmdnode	*eval_semi(t_cmdnode *a, t_cmdnode *b)
{
	exec_cmd(a, NO, NULL, NULL);
	return (b);
}

static t_cmdnode	*eval_ast(t_btree *node, pid_t *pids)
{
	t_astnode	*ndat;
	t_cmdnode	*leftnode;
	t_cmdnode	*rightnode;

	if (!node)
		return (NULL);
	ndat = (t_astnode*)node->data;
	if (ndat->data)
		return ((t_cmdnode*)ndat->data);
	leftnode = eval_ast(node->left, pids);
	rightnode = eval_ast(node->right, pids);
	if (ndat->type == PIPE)
		return (eval_pipe(leftnode, rightnode, pids));
	clean_pipes(pids);
	if (ndat->type == SEMI)
		return (eval_semi(leftnode, rightnode));
	return (NULL);
}

int					eval_line(char *line)
{
	int		ret;
	t_list	*tokens;
	t_btree	*ast;
	pid_t	pids[11];

	if (!(tokens = lex_line(line)))
		return (EXIT_SUCCESS);
	parser_check_heredocs(tokens);
	if (!(ast = parse_tokens(tokens)))
		return (ft_returnmsg("eval_line: ast error", STDERR_FILENO, 258));
	ft_bzero(pids, sizeof(pids) - sizeof(pid_t));
	pids[sizeof(pids) / sizeof(pid_t) - 1] = -1;
	ret = exec_cmd(eval_ast(ast, pids), NO, NULL, NULL);
	clean_pipes(pids);
	ft_btdel(&ast, &ast_btdel);
	ft_lstdel(&tokens, &tokens_lstdel);
	set_env_var_n(NULL, "?", ret);
	return (ret);
}
