/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 20:14:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/28 08:08:57 by kdumarai         ###   ########.fr       */
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

void				add_token(t_list **tokens, char *s)
{
	t_list	*newtok;
	size_t	len;

	if (!s || (len = ft_strlen(s)) < 1)
		return ;
	newtok = ft_lstnew(NULL, 0);
	if (!(newtok->content = (void*)ft_strdup(s)))
	{
		free(newtok);
		return ;
	}
	newtok->content_size = len + 1;
	ft_lstpush(tokens, newtok);
}

/*static t_lexstate	get_nextstate(t_list **ret,
								t_lexstate curr_state,
								char **currtokstr,
								char c)
{
	t_charstate	char_state;

	char_state = get_charstate(c);
	if (curr_state == kLexStateGeneral && char_state == kCharStateSpace)
	{
		add_token(ret, *currtokstr);
		free(*currtokstr);
		*currtokstr = ft_strnew(0);
		return (kLexStateGeneral);
	}
	if (char_state == kCharStateGeneral || (curr_state == kLexStateDQuote && char_state != kCharStateDQuote))
	{
		ft_strnadd(currtokstr, &c, 1);
		return (kLexStateGeneral);
	}
	if (curr_state == kLexStateGeneral && char_state == kCharStateDQuote)
		return (kLexStateDQuote);
	if (curr_state == kLexStateDQuote && char_state == kCharStateDQuote)
		return (kLexStateGeneral);
	return (kLexStateUndefined);
}*/

static t_lexstate	get_nextstate(t_list **ret,
								t_lexstate curr_state,
								char **currtokstr,
								char c)
{
	const t_charstate	char_state = get_charstate(c);
	const int			combs[6] = {1000 * kLexStateGeneral + kCharStateGeneral,
									1000 * kLexStateGeneral + kCharStateDQuote,
									1000 * kLexStateGeneral + kCharStateSpace,
									1000 * kLexStateDQuote + kCharStateGeneral,
									1000 * kLexStateDQuote + kCharStateDQuote,
									1000 * kLexStateDQuote + kCharStateSpace};
	static t_lexstate	(*act[6])(t_list**, char**, char, t_lexstate) =
	{&add_to_curr, &switch_to_dquote, &add_token_to_ret,
	&add_to_curr, &switch_to_general, &add_to_curr};
	unsigned int		idx;

	idx = 0;
	while (idx < sizeof(combs) / sizeof(int))
	{
		if (1000 * curr_state + char_state == combs[idx])
			return ((act[idx])(ret, currtokstr, c, curr_state));
		idx++;
	}
	return (kLexStateUndefined);
}

t_list				*lex_line(char *line)
{
	t_list		*ret;
	char		*currtokstr;
	t_lexstate	curr_state;

	if (!line)
		return (NULL);
	ret = NULL;
	currtokstr = ft_strnew(0);
	curr_state = kLexStateGeneral;
	while (*line)
	{
		curr_state = get_nextstate(&ret, curr_state, &currtokstr, *line);
		line++;
	}
	add_token(&ret, currtokstr);
	return (ret);
}
