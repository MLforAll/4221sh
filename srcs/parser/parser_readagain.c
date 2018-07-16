/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_readagain.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 23:44:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/16 17:12:46 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh.h"

static char					*read_till_delim(const char *prompt,
											char *delim,
											t_uint8 whole)
{
	char		*ret;
	char		*line;
	t_rl_opts	opts;

	ret = NULL;
	ft_bzero(&opts, sizeof(t_rl_opts));
	line = NULL;
	while (TRUE)
	{
		if (!(line = ft_readline(prompt, &opts, NULL))
			|| (delim && ft_strcmp(line, delim) == 0 && whole))
		{
			free(line);
			break ;
		}
		ft_stradd(&ret, line);
		ft_strdel(&line);
		if (!delim || (delim && !whole && ft_strstr(line, delim)))
			break ;
		ft_stradd(&ret, "\n");
	}
	return (ret);
}

int							parser_check_heredocs(t_dlist *tokens,
												t_uint8 ragain)
{
	t_token	*tok;
	char	**toks_dest;
	char	*tmp;

	tok = (t_token*)tokens->content;
	if (tok->type != DLESS)
		return (FALSE);
	if (!tokens->next || !tokens->next->content)
		return (-1);
	if (((t_token*)tokens->next->content)->type == WORD && ragain)
	{
		toks_dest = &((t_token*)tokens->next->content)->s;
		tmp = read_till_delim(SH_HEREDOC_PR, *toks_dest, YES);
		free(*toks_dest);
		*toks_dest = tmp;
		return (TRUE);
	}
	return (FALSE);
}

inline static const char	*parser_inclist_types(t_toktype ttype)
{
	const t_toktype	types[] = {PIPE, AND_IF, OR_IF};
	const char		*prs[] = {SH_PIPE_PR, SH_ANDIF_PR, SH_ORIF_PR};
	t_uint8			idx;

	idx = 0;
	while (idx < sizeof(types) / sizeof(t_toktype))
	{
		if (ttype == types[idx])
			return (prs[idx]);
		idx++;
	}
	return (NULL);
}

t_uint8						parser_check_inclist(char **line,
												t_dlist **tokens,
												t_dlist *tmp)
{
	const char	*extraprompt;
	char		*extraline;
	t_dlist		*extra;

	extraline = NULL;
	if (!(extraprompt = parser_inclist_types(((t_token*)tmp->content)->type)))
		return (TRUE);
	if (!line)
		return (FALSE);
	extraline = read_till_delim(extraprompt, NULL, NO);
	if (!extraline)
		return (FALSE);
	if (!*extraline)
		return (free_return((void**)&extraline, TRUE));
	ft_stradd(line, extraline);
	extra = lex_line(extraline);
	free(extraline);
	ft_dlstpush(tokens, extra);
	return ((extra != NULL));
}
