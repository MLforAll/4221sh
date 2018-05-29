/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 20:14:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/28 23:35:01 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh.h"

void				tokens_lstdel(void *data, size_t datsize)
{
	(void)datsize;
	free(((t_token*)data)->toks);
	free(data);
}

static size_t		get_charstate(t_charstate *cs, char *s)
{
	unsigned int		idx;
	const char			*chars[] = {">>", ">", "<<", "<", "&", "-",
									";", "|", "\"", "'", "\\", " "};
	const t_charstate	st[] = {kCharDGreat, kCharGreat, kCharDLess, kCharLess,
								kCharAmpersand, kCharDash, kCharSemi, kCharPipe,
								kCharDQuote, kCharSQuote, kCharEscape,
								kCharSpace};

	if (!*s)
	{
		*cs = kCharNull;
		return (1);
	}
	idx = 0;
	while (idx < sizeof(chars) / sizeof(char*))
	{
		if (ft_strstart(s, (char*)chars[idx]))
		{
			*cs = st[idx];
			return (ft_strlen(chars[idx]));
		}
		++idx;
	}
	*cs = kCharGeneral;
	return (1);
}

void				add_token(t_list **toks, char *s, t_toktype type, int prio)
{
	char	*tmp;
	t_list	*newtok;
	t_token	tokdat;

	if (!s || (ft_strlen(s) < 1))
		return ;
	ft_bzero(&tokdat, sizeof(t_token));
	if (s[0] == '$' && s[1])
	{
		if ((tmp = get_lvar(s + 1))
			|| (tmp = getenv(s + 1)))
			s = tmp;
		else
			s = "";
	}
	if (s[0] == '~' && (tmp = getenv("HOME"))
		&& (tmp = ft_strjoin(tmp, s + 1)))
		tokdat.toks = tmp;
	else if (!(tokdat.toks = ft_strdup(s)))
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
	size_t		jmp;

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
		jmp = get_charstate(&dat.cs, line);
		dat.curr_state = get_nextstate(&dat);
		if (!*line)
			break ;
		line += jmp;
	}
	ft_strdel(&dat.currtoks);
	return (ret);
}
