/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 20:14:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/08 23:22:03 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_lexer.h"

t_charstate		get_charstate(char c)
{
	if (c == '>')
		return (kCharGreat);
	if (c == '|')
		return (kCharPipe);
	if (c == '"')
		return (kCharDQuote);
	if (c == '\'')
		return (kCharSQuote);
	if (c == '\\')
		return (kCharEscape);
	if (c == ' ')
		return (kCharSpace);
	if (c == '\0')
		return (kCharNull);
	return (kCharGeneral);
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

static t_lexstate	get_nextstate(t_lexdat *dat)
{
	/*const t_equi		eq[16] = {
	{1000 * kLexStateGeneral + kCharGeneral, &add_to_curr, (void*)dat},
	{1000 * kLexStateGeneral + kCharDQuote, &switch_to_dquote, (void*)dat},
	{1000 * kLexStateGeneral + kCharSpace, &add_token_to_ret, (void*)dat},
	{1000 * kLexStateGeneral + kCharGreat, &switch_to_great, (void*)dat},
	{1000 * kLexStateGeneral + kCharPipe, &create_pipe_tok, (void*)dat},
	{1000 * kLexStateDQuote + kCharGeneral, &add_to_curr, (void*)dat},
	{1000 * kLexStateDQuote + kCharDQuote, &switch_to_general, (void*)dat},
	{1000 * kLexStateDQuote + kCharSpace, &add_to_curr, (void*)dat},
	{1000 * kLexStateDQuote + kCharGreat, &add_to_curr, (void*)dat},
	{1000 * kLexStateDQuote + kCharPipe, &add_to_curr, (void*)dat},
	{1000 * kLexStateGreat + kCharGeneral, &create_great_tok2, (void*)dat},
	{1000 * kLexStateGreat + kCharDQuote, &create_great_tok2, (void*)dat},
	{1000 * kLexStateGreat + kCharSpace, &create_great_tok, (void*)dat},
	{1000 * kLexStateGreat + kCharGreat, &create_dgreat_tok, (void*)dat},
	{1000 * kLexStateGreat + kCharPipe, &create_clobber_tok, (void*)dat},
	{0, NULL, NULL}};*/
	const t_equi		eq[4] = {
	{kLexStateGeneral, &lex_general, (void*)dat},
	{kLexStateDQuote, &lex_dquote, (void*)dat},
	{kLexStateGreat, &lex_great, (void*)dat},
	{0, NULL, NULL}};
	/*const t_charstate	char_state = get_charstate(dat->c);
	const int			cmpdat = 1000 * dat->curr_state + char_state;*/
	const int			cmpdat = dat->curr_state;
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
	add_token(&ret, dat.currtoks, WORD);
	ft_strdel(&dat.currtoks);
	return (ret);
}
