/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 20:14:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/22 17:03:48 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

void				tokens_lstdel(void *data, size_t datsize)
{
	(void)datsize;
	free(((t_token*)data)->toks);
	free(data);
}

t_charstate			get_charstate(char c)
{
	const char		*chars[] = {"\0", ">", "<", "&", "-", ";", "|", "\"", "'",
								"\\", " "};
	t_charstate		st[] = {kCharNull, kCharGreat, kCharLess, kCharAmpersand,
							kCharDash, kCharSemi, kCharPipe, kCharDQuote,
							kCharSQuote, kCharEscape, kCharSpace};
	unsigned int	idx;

	idx = 0;
	while (idx < sizeof(chars) / sizeof(char*))
	{
		if (ft_strnequ(chars[idx], &c, 1))
			return (st[idx]);
		idx++;
	}
	return (kCharGeneral);
}

void				add_token(t_list **toks, char *s, t_toktype type, int prio)
{
	t_list	*newtok;
	t_token	tokdat;

	if (s && (ft_strlen(s) < 1))
		return ;
	ft_bzero(&tokdat, sizeof(t_token));
	if (s && !(tokdat.toks = ft_strdup(s)))
		return ;
	tokdat.type = type;
	tokdat.priority = prio;
	if (!(newtok = ft_lstnew(&tokdat, sizeof(t_token))))
		return ;
	ft_lstpush(toks, newtok);
}

static t_lexstate	get_nextstate(t_lexdat *dat)
{
	const t_equi		eq[6] = {
	{kLexStateGeneral, &lex_general, (void*)dat},
	{kLexStateDQuote, &lex_dquote, (void*)dat},
	{kLexStateGreat, &lex_great, (void*)dat},
	{kLexStateLess, &lex_less, (void*)dat},
	{kLexStateAmpersand, &lex_ampersand, (void*)dat},
	{0, NULL, NULL}};
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
	while (42)
	{
		dat.c = *line;
		dat.curr_state = get_nextstate(&dat);
		if (!*line)
			break ;
		line++;
	}
	ft_strdel(&dat.currtoks);
	return (ret);
}