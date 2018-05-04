/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 20:14:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/30 15:38:31 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "bl.h"

static t_charstate	get_charstate(char c)
{
	if (c == '>')
		return (kCharStateRedir);
	if (c == '|')
		return (kCharStatePipe);
	if (c == '"')
		return (kCharStateDQuote);
	if (c == ' ')
		return (kCharStateSpace);
	if (c == '\0')
		return (kCharStateNull);
	return (kCharStateGeneral);
}

void				add_token(t_list **tokens, char *s, t_toktype type)
{
	t_list	*newtok;
	t_token	tokdat;

	if (s && (ft_strlen(s) < 1))
		return ;
	ft_bzero(&tokdat, sizeof(t_token));
	if (s && !(tokdat.toks = ft_strdup(s)))
		return ;
	tokdat.type = type;
	if (!(newtok = ft_lstnew(&tokdat, sizeof(t_token))))
		return ;
	ft_lstpush(tokens, newtok);
}

static int			ft_swcmp(void *p1, void *p2)
{
	const int	a = *(int*)p1;
	const int	b = *(int*)p2;

	return ((a == b));
}

static t_lexstate	get_nextstate(t_lexdat *dat)
{
	const t_equi		eq[16] = {
	{1000 * kLexStateGeneral + kCharStateGeneral, &add_to_curr, (void*)dat},
	{1000 * kLexStateGeneral + kCharStateDQuote, &switch_to_dquote, (void*)dat},
	{1000 * kLexStateGeneral + kCharStateSpace, &add_token_to_ret, (void*)dat},
	{1000 * kLexStateGeneral + kCharStateRedir, &create_redir_tok, (void*)dat},
	{1000 * kLexStateGeneral + kCharStatePipe, &create_pipe_tok, (void*)dat},
	{1000 * kLexStateDQuote + kCharStateGeneral, &add_to_curr, (void*)dat},
	{1000 * kLexStateDQuote + kCharStateDQuote, &switch_to_general, (void*)dat},
	{1000 * kLexStateDQuote + kCharStateSpace, &add_to_curr, (void*)dat},
	{1000 * kLexStateDQuote + kCharStateRedir, &add_to_curr, (void*)dat},
	{1000 * kLexStateDQuote + kCharStatePipe, &add_to_curr, (void*)dat},
	{0, NULL, NULL}};
	const t_charstate	char_state = get_charstate(dat->c);
	const int			cmpdat = 1000 * dat->curr_state + char_state;
	int					ret;

	ret = ft_switch((void*)&cmpdat, (void*)&eq, sizeof(t_equi), &ft_swcmp);
	return ((ret > 0) ? (t_lexstate)ret : kLexStateUndefined);
}

t_list				*lex_line(char *line)
{
	t_list		*ret;
	t_lexdat	dat;

	if (!line)
		return (NULL);
	ret = NULL;
	ft_bzero(&dat, sizeof(t_lexdat));
	dat.currtoks = ft_strnew(0);
	dat.ret = &ret;
	dat.curr_state = kLexStateGeneral;
	while (*line)
	{
		dat.c = *line;
		dat.curr_state = get_nextstate(&dat);
		line++;
	}
	add_token(&ret, dat.currtoks, kTokTypeGeneral);
	ft_strdel(&dat.currtoks);
	return (ret);
}
