/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_eval.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 22:22:21 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/04 02:55:28 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "sh.h"

static void			clean_pipes(t_tab *pids)
{
	unsigned long	idx;
	pid_t			*curr;

	idx = pids->count;
	while (idx--)
	{
		curr = &((pid_t*)pids->data)[idx];
		if (*curr > 0)
		{
			waitpid(*curr, NULL, 0);
			*curr = 0;
		}
	}
}

static t_cmdnode	*eval_pipe(t_cmdnode *a, t_cmdnode *b, t_tab *pids)
{
	int		pfd[2];
	pid_t	pid;

	pipe(pfd);
	a->stdout_fd = pfd[1];
	ft_memcpy(a->pfd, pfd, sizeof(pfd));
	b->stdin_fd = pfd[0];
	ft_memcpy(b->pfd, pfd, sizeof(pfd));
	exec_cmd(a, YES, &pid, NULL);
	ft_ttabcat(pids, &pid, 1);
	return (b);
}

static t_cmdnode	*eval_semi(t_cmdnode *a, t_cmdnode *b)
{
	if (!b)
		return (a);
	exec_cmd(a, NO, NULL, NULL);
	return (b);
}

static t_cmdnode	*eval_ast(t_btree *node, t_tab *pids)
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

int					eval_line(char **line, t_uint8 ragain)
{
	int		ret;
	t_list	*tokens;
	t_btree	*ast;
	t_tab	pids;

	if (!line || !(tokens = lex_line(*line)))
		return (EXIT_SUCCESS);
	if (!(ast = parse_tokens((ragain) ? line : NULL, tokens)))
		return (ft_returnmsg("eval_line: ast error", STDERR_FILENO, 258));
	pids = ft_ttabnew(sizeof(pid_t));
	ret = exec_cmd(eval_ast(ast, &pids), NO, NULL, NULL);
	clean_pipes(&pids);
	ft_ttabdel(&pids, NULL);
	ft_btdel(&ast, &ast_btdel);
	ft_lstdel(&tokens, &tokens_lstdel);
	(void)set_lvar_n("?", ret);
	return (ret);
}
