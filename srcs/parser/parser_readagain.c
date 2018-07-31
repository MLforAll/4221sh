/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_readagain.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 23:44:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/31 02:41:28 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"

static int					read_both(char **line,
									const char *prompt,
									t_rl_opts *ftrl_opts,
									int fd)
{
	int		status;

	if (fd == -1)
		return (ft_readline(line, prompt, ftrl_opts, NULL));
	status = get_next_line(fd, line);
	if (status == -1)
		return (FTRL_FAIL);
	if (status == 0)
		return (FTRL_EOF);
	return (FTRL_OK);
}

static char					*read_till_delim(const char *prompt,
											const char *delim,
											t_uint8 opts, int fd)
{
	int			status;
	char		*ret;
	char		*line;
	t_rl_opts	ftrl_opts;

	ret = (opts & RA_BEFORE) ? ft_strdup("\n") : NULL;
	ft_bzero(&ftrl_opts, sizeof(t_rl_opts));
	while (TRUE)
	{
		if ((status = read_both(&line, prompt, &ftrl_opts, fd)) == FTRL_SIGINT
			|| status == FTRL_FAIL)
		{
			ft_strdel(&ret);
			return (NULL);
		}
		if (status == FTRL_EOF || (ft_strequ(line, delim) && (opts & RA_WHOLE)))
			break ;
		ft_stradd(&ret, line);
		if (!delim || (delim && (opts & !RA_WHOLE) && ft_strstr(line, delim)))
			break ;
		ft_strdel(&line);
		ft_stradd(&ret, "\n");
	}
	ft_strdel(&line);
	return (ret);
}

int							parser_check_heredocs(t_dlist *tokens, int fd)
{
	t_token	*tok;
	char	**toks_dest;
	char	*tmp;

	tok = (t_token*)tokens->content;
	if (tok->type != DLESS)
		return (FALSE);
	if (!tokens->next || !tokens->next->content)
		return (-1);
	if (((t_token*)tokens->next->content)->type == WORD)
	{
		toks_dest = &((t_token*)tokens->next->content)->s;
		if (!(tmp = read_till_delim(SH_HEREDOC_PR, *toks_dest, RA_WHOLE, fd)))
			tmp = ft_strnew(0);
		free(*toks_dest);
		*toks_dest = tmp;
		return (TRUE);
	}
	return (FALSE);
}

inline static const char	*parser_inclist_types(t_token *tok)
{
	const t_toktype	types[] = {PIPE, AND_IF, OR_IF};
	const char		*prs[] = {SH_PIPE_PR, SH_ANDIF_PR, SH_ORIF_PR};
	t_uint8			idx;

	if (!tok)
		return ("readagain> ");
	idx = 0;
	while (idx < sizeof(types) / sizeof(t_toktype))
	{
		if (tok->type == types[idx])
			return (prs[idx]);
		idx++;
	}
	return (NULL);
}

t_uint8						parser_check_inclist(char **line,
												t_dlist **tokens,
												t_dlist *tmp, int fd)
{
	const char	*prompt;
	char		*extraline;
	int			lex_ret;

	if (!line)
		return (FALSE);
	if (!(prompt = parser_inclist_types(tmp ? (t_token*)tmp->content : NULL)))
		return (TRUE);
	if (!(extraline = read_till_delim(prompt, NULL, 0, fd)))
		return (FALSE);
	if (!*extraline)
	{
		free(extraline);
		return (TRUE);
	}
	if (!tmp)
		(*line)[ft_strlen(*line) - 1] = '\0';
	ft_stradd(line, extraline);
	lex_ret = lex_line(tokens, extraline);
	free(extraline);
	return (lex_ret != LEXER_FAIL);
}

t_uint8						parser_check_ret(char **line,
											t_dlist **tokens,
											const char *prompt,
											const char *delim)
{
	char	*extraline;
	int		lex_ret;
	int		add_ret;

	if (!(extraline = read_till_delim(prompt, delim, RA_BEFORE, -1)))
		return (FALSE);
	lex_ret = lex_line(tokens, extraline);
	add_ret = (line) ? ft_stradd(line, extraline) : TRUE;
	free(extraline);
	return (add_ret && lex_ret != LEXER_FAIL);
}
