/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_eval.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 22:22:21 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/27 06:21:43 by kdumarai         ###   ########.fr       */
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
			(void)waitpid(*curr, NULL, WUNTRACED);
			*curr = 0;
		}
	}
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
	if (ndat->type == AND_IF)
		return (eval_andif(leftnode, rightnode));
	if (ndat->type == OR_IF)
		return (eval_orif(leftnode, rightnode));
	if (ndat->type == AMPERSAND)
		return (eval_background(leftnode, rightnode));
	return (NULL);
}

int					eval_line(char **line, t_uint8 ragain)
{
	int			ret;
	int			lex_ret;
	t_dlist		*tokens;
	t_btree		*ast;
	t_tab		pids;

	if (!line || !*line)
		return (EXIT_SUCCESS);
	tokens = NULL;
	if ((lex_ret = lex_line(&tokens, *line)) == LEXER_FAIL)
		return (ft_returnmsg("lex_line(): fatal error", 2, 1));
	if (!tokens)
		return (EXIT_SUCCESS);
	if (!(ast = parse_tokens((ragain) ? line : NULL, tokens, lex_ret)))
		return (PARSER_FAIL);
	(void)ft_ttabnew(&pids, sizeof(pid_t));
	ret = exec_cmd(eval_ast(ast, &pids), NO, NULL, NULL);
	clean_pipes(&pids);
	ft_ttabdel(&pids, NULL);
	ft_btdel(&ast, &ast_btdel);
	ft_dlstdel(&tokens, &tokens_lstdel);
	(void)set_lvar_n("?", ret);
	return (ret);
}
