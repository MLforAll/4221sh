/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 20:14:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/26 23:13:57 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "bl.h"

static t_charstate	get_charstate(char c)
{
	if (c == '"')
		return (kCharStateDQuote);
	if (c == ' ')
		return (kCharStateSpace);
	if (c == '\0')
		return (kCharStateNull);
	return (kCharStateGeneral);
}

static void			add_token(t_list **tokens, char *s)
{
	t_list	*newtok;

	if (!s)
		return ;
	newtok = ft_lstnew(NULL, 0);
	if (!(newtok->content = (void*)ft_strdup(s)))
	{
		free(newtok);
		return ;
	}
	newtok->content_size = ft_strlen(s) + 1;
	ft_lstpush(tokens, newtok);
}

t_list				*lex_line(char *line)
{
	t_list		*ret;
	char		*currtokstr;
	t_lexstate	curr_state;
	t_charstate	char_state;
	t_lexstate	next_state;

	if (!line)
		return (NULL);
	ret = NULL;
	currtokstr = ft_strnew(0);
	curr_state = kLexStateGeneral;
	next_state = kLexStateUndefined;
	while (*line)
	{
		char_state = get_charstate(*line);
		if (char_state == kCharStateGeneral || (curr_state == kLexStateDQuote && char_state != kCharStateDQuote))
		{
			ft_strnadd(&currtokstr, line, 1);
			next_state = curr_state;
		}
		if (curr_state == kLexStateGeneral && char_state == kCharStateSpace)
		{
			add_token(&ret, currtokstr);
			free(currtokstr);
			currtokstr = ft_strnew(0);
			next_state = curr_state;
		}
		if (curr_state == kLexStateGeneral && char_state == kCharStateDQuote)
			next_state = kLexStateDQuote;
		if (curr_state == kLexStateDQuote && char_state == kCharStateDQuote)
			next_state = kLexStateGeneral;
		line++;
		curr_state = next_state;
	}
	add_token(&ret, currtokstr);
	return (ret);
}
