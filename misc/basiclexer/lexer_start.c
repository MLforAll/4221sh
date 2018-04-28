/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 20:14:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/28 10:02:07 by kdumarai         ###   ########.fr       */
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

static t_lexstate	get_nextstate(t_lexdat *dat)
{
	const t_equi		eq[7] = {
	{1000 * kLexStateGeneral + kCharStateGeneral, &add_to_curr, (void*)dat},
	{1000 * kLexStateGeneral + kCharStateDQuote, &switch_to_dquote, (void*)dat},
	{1000 * kLexStateGeneral + kCharStateSpace, &add_token_to_ret, (void*)dat},
	{1000 * kLexStateDQuote + kCharStateGeneral, &add_to_curr, (void*)dat},
	{1000 * kLexStateDQuote + kCharStateDQuote, &switch_to_general, (void*)dat},
	{1000 * kLexStateDQuote + kCharStateSpace, &add_to_curr, (void*)dat},
	{1000 * kLexStateDQuote + kCharStateSpace, NULL, NULL}};
	const t_charstate	char_state = get_charstate(dat->c);
	const int			cmpdat = 1000 * dat->curr_state + char_state;
	int					ret;

	ret = ft_switch((void*)&cmpdat, (void*)&eq, sizeof(t_equi), &ft_swcmp);
	return ((ret > 0) ? (t_lexstate)ret : kLexStateUndefined);
}

t_list				*lex_line(char *line)
{
	t_list		*ret;
	char		*currtokstr;
	t_lexstate	curr_state;
	t_lexdat	dat;

	if (!line)
		return (NULL);
	ret = NULL;
	currtokstr = ft_strnew(0);
	curr_state = kLexStateGeneral;
	while (*line)
	{
		dat.ret = &ret;
		dat.curr_state = curr_state;
		dat.currtokstr = &currtokstr;
		dat.c = *line;
		curr_state = get_nextstate(&dat);
		line++;
	}
	add_token(&ret, currtokstr);
	return (ret);
}
