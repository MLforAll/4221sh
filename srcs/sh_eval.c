/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_eval.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 22:22:21 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/13 01:07:19 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"

static t_cmdnode	*eval_pipe(t_cmdnode *a, t_cmdnode *b)
{
	int		pfd[2];

	(void)a;
	(void)b;
	pipe(pfd);
	a->stdout_fd = pfd[1];
	b->stdin_fd = pfd[0];
	exec_cmd(a, NULL);
	return (b);
}

static t_cmdnode	*eval_semi(t_cmdnode *a, t_cmdnode *b)
{
	exec_cmd(a, NULL);
	exec_cmd(b, NULL);
	return (NULL);
}

static t_cmdnode	*eval_ast(t_btree *node)
{
	t_astnode	*ndat;

	if (!node)
		return (NULL);
	ndat = (t_astnode*)node->data;
	if (ndat->data)
		return ((t_cmdnode*)ndat->data);
	if (ndat->type == PIPE)
		return (eval_pipe(eval_ast(node->left), eval_ast(node->right)));
	if (ndat->type == SEMI)
		return (eval_semi(eval_ast(node->left), eval_ast(node->right)));
	return (NULL);
}

int					exec_cmds(char *line)
{
	int		ret;
	t_list	*tokens;
	t_btree	*ast;
	
	ret = EXIT_SUCCESS;
	if (!(tokens = lex_line(line)))
		return (ft_returnmsg("exec_cmds: tokens error", STDERR_FILENO, 258));
	if (!(ast = parse_tokens(tokens)))
		return (ft_returnmsg("exec_cmds: ast error", STDERR_FILENO, 259));
	ret = exec_cmd(eval_ast(ast), NULL);
	ft_btdel(&ast, &ast_btdel);
	ft_lstdel(&tokens, &tokens_lstdel);
	return (ret);
}
