/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_readagain.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 23:44:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/19 19:36:42 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftreadline.h"
#include "sh_parser.h"
#include "sh.h"

static char	*read_till_delim(const char *prompt, char *delim, uint8_t whole)
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
			break ;
		ft_stradd(&ret, line);
		ft_strdel(&line);
		if (!delim || (delim && !whole && ft_strstr(line, delim)))
			break ;
		ft_stradd(&ret, "\n");
	}
	return (ret);
}

void		parser_check_heredocs(t_list *tokens)
{
	char	**toks_dest;
	char	*tmp;

	while (tokens)
	{
		if (((t_token*)tokens->content)->type == DLESS
			&& tokens->next->content
			&& ((t_token*)tokens->next->content)->type == WORD)
		{
			toks_dest = &((t_token*)tokens->next->content)->toks;
			tmp = read_till_delim(SH_HEREDOC_PR, *toks_dest, YES);
			free(*toks_dest);
			*toks_dest = tmp;
		}
		tokens = tokens->next;
	}
}

uint8_t		parser_check_inclist(t_list **tokens)
{
	t_toktype	ttype;
	t_list		*tmp;
	char		*extraline;
	t_list		*extra;

	if (!tokens)
		return (FALSE);
	tmp = *tokens;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
		return (FALSE);
	extra = NULL;
	ttype = ((t_token*)tmp->content)->type;
	if (ttype == PIPE)
	{
		extraline = read_till_delim(SH_PIPE_PR, NULL, NO);
		extra = lex_line(extraline);
		free(extraline);
	}
	ft_lstpush(tokens, extra);
	return ((extra != NULL));
}

void		parser_check_quote(t_list **tokens)
{
	(void)tokens;
}
