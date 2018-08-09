/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_inclist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 23:44:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/09 21:37:40 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"

static const char	*parser_inclist_types(t_token *tok)
{
	const t_toktype	types[] = {PIPE, AND_IF, OR_IF};
	const char		*prs[] = {SH_PIPE_PR, SH_ANDIF_PR, SH_ORIF_PR};
	t_uint8			idx;

	if (!tok)
		return (SH_READAGAIN_PR);
	idx = 0;
	while (idx < sizeof(types) / sizeof(t_toktype))
	{
		if (tok->type == types[idx])
			return (prs[idx]);
		idx++;
	}
	return (NULL);
}

int					parser_check_inclist(char **line,
										t_dlist **tokens,
										t_dlist *tmp, int fd)
{
	const char		*prompt;
	char			*extraline;
	int				lret;
	struct s_raconf	conf;

	if (!(prompt = parser_inclist_types(tmp ? (t_token*)tmp->content : NULL)))
		return (RA_NOTHING);
	get_raconf(&conf, prompt, NULL, RACONF_AC | RACONF_BELL);
	if (!(extraline = read_till_delim(&conf, 0, fd)))
		return (RA_ABORT);
	if (!*extraline)
	{
		free(extraline);
		return (LEXER_OK);
	}
	if (!tmp && line)
		(*line)[ft_strlen(*line) - 1] = '\0';
	if ((lret = lex_line(tokens, extraline)) == LEXER_FAIL
		|| (line && !ft_stradd(line, extraline)))
	{
		free(extraline);
		return (LEXER_FAIL);
	}
	free(extraline);
	return (lret);
}

int					parser_check_ret(char **line,
									t_dlist **tokens,
									const char *delim, int fd)
{
	char			*extraline;
	int				lret;
	const char		*prompt = (ft_strequ(delim, "'")) ? "squote> " : "dquote> ";
	struct s_raconf	conf;

	get_raconf(&conf, prompt, delim, RACONF_BELL);
	if (!(extraline = read_till_delim(&conf, RA_BEFORE, fd)))
		return (RA_ABORT);
	if ((lret = lex_line(tokens, extraline)) == LEXER_FAIL
		|| (line && !ft_stradd(line, extraline)))
		return (LEXER_FAIL);
	free(extraline);
	return (lret);
}
