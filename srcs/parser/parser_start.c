/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 16:55:22 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/02 22:28:31 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"

inline static t_btree	*parse_error(const char *tok)
{
	ft_putstr_fd(g_sh_name, STDERR_FILENO);
	ft_putstr_fd(": syntax error near unexpected token `", STDERR_FILENO);
	ft_putstrsec_fd(tok, STDERR_FILENO);
	ft_putendl_fd("`", STDERR_FILENO);
	return (NULL);
}

static t_uint8			preparse_readagain(char **line,
											t_dlist **tokens,
											int lret, int fd)
{
	const char	*delim;

	while (lret != LEXER_OK)
	{
		if (lret == LEXER_INC)
			lret = parser_check_inclist(line, tokens, NULL, fd);
		else
		{
			delim = (lret == LEXER_INCDQ) ? "\"" : "'";
			lret = parser_check_ret(line, tokens, delim, fd);
			if (lret == RA_ABORT && fd != -1)
				(void)parse_error("EOF");
		}
		if (lret == LEXER_FAIL)
		{
			sh_err(SH_ERR_MALLOC, "parse_tokens()", NULL);
			return (FALSE);
		}
		if (lret == RA_ABORT)
			return (FALSE);
	}
	return (TRUE);
}

/*
** todo: try reversal of syntax err chk and inclst conditions and rem of else
*/

t_btree					*parse_tokens(char **line, \
									t_dlist *tokens, \
									int lret, \
									int fd)
{
	int		heredocs;
	char	*syntax_err;
	t_dlist	*tokbw;

	tokbw = tokens;
	while (tokbw)
	{
		if (tokbw == tokens && lret >= LEXER_INC
			&& !preparse_readagain(line, &tokens, lret, fd))
			return (NULL);
		syntax_err = NULL;
		if ((heredocs = parser_check_heredocs(tokbw, fd)) == -1)
			syntax_err = ((t_token*)tokbw->content)->s;
		if (syntax_err || (syntax_err = parser_check_syntax(tokbw)))
			return (parse_error(syntax_err));
		if (!tokbw->next && ((t_token*)tokbw->content)->type != WORD)
			lret = parser_check_inclist(line, &tokens, tokbw, fd);
		tokbw = tokbw->next;
	}
	return (parser_create_ast(tokens));
}
