/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_eval.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 22:22:21 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/07 01:30:24 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "sh.h"

static void		clean_pipes(t_tab *pids)
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

t_cmdnode		*eval_ast(t_btree *node, t_tab *pids)
{
	t_astnode	*ndat;

	if (!node)
		return (NULL);
	ndat = (t_astnode*)node->data;
	if (ndat->data)
		return ((t_cmdnode*)ndat->data);
	if (ndat->type == PIPE)
		return (eval_pipe(node, pids));
	clean_pipes(pids);
	if (ndat->type == SEMI)
		return (eval_semi(node, pids));
	if (ndat->type == AND_IF)
		return (eval_andif(node, pids));
	if (ndat->type == OR_IF)
		return (eval_orif(node, pids));
	if (ndat->type == AMPERSAND)
		return (eval_background(node, pids));
	return (NULL);
}

int				eval_line(char **line, int fd)
{
	int			ret;
	int			lex_ret;
	t_dlist		*tokens;
	t_btree		*ast;
	t_tab		pids;

	if (!line || !*line || !**line)
		return (-1);
	tokens = NULL;
	if ((lex_ret = lex_line(&tokens, *line)) == LEXER_FAIL)
		return (sh_err_ret(SH_ERR_MALLOC, "lex_line()", NULL, EXIT_FAILURE));
	if (!tokens)
		return (EXIT_SUCCESS);
	if (!(ast = parse_tokens((fd == -1) ? line : NULL, tokens, lex_ret, fd)))
	{
		ft_dlstdel(&tokens, &tokens_lstdel);
		return (PARSER_FAIL);
	}
	(void)ft_ttabnew(&pids, sizeof(pid_t));
	ret = exec_cmd(eval_ast(ast, &pids), NO, NULL, NULL);
	clean_pipes(&pids);
	ft_ttabdel(&pids, NULL);
	ft_btdel(&ast, &ast_btdel);
	ft_dlstdel(&tokens, &tokens_lstdel);
	return (ret);
}
