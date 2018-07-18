/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 20:14:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/18 21:52:38 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

void				tokens_lstdel(void *data, size_t datsize)
{
	(void)datsize;
	free(((t_token*)data)->s);
	free(data);
}

static size_t		get_charstate(t_charstate *cs, char *s)
{
	unsigned short		idx;
	const char			*chars[] = {">>", ">", "<<", "<", "&", "-",
									";", "|", "\"", "'", "\\", " ", "\t"};
	const t_charstate	st[] = {kCharDGreat, kCharGreat, kCharDLess, kCharLess,
								kCharAmpersand, kCharDash, kCharSemi, kCharPipe,
								kCharDQuote, kCharSQuote, kCharEscape,
								kCharSpace, kCharTab};

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

/*
** 4 args -> problem -> no info on quoting
** Solutions:
**	1. rm priority, add a func to parser
**	2. have a custom t_currtok struct in lexdat_t and pass it instead of vs, type and prio
*/

void				add_token(t_dlist **tokens,
							t_str *vs,
							t_toktype type,
							int prio)
{
	t_dlist	*newtok;
	t_token	tokdat;
	char	*cpy;
	int		cpy_isalloced;

	if (!vs || (ft_strlen(vs->s) < 1))
		return ;
	ft_bzero(&tokdat, sizeof(t_token));
	cpy = vs->s;
	cpy_isalloced = (lexer_expand_tilde(&cpy) || lexer_expand_var(&cpy));
	if (!(tokdat.s = ft_strdup(cpy)))
		return ;
	tokdat.type = type;
	tokdat.priority = prio;
	tokdat.quoting = kNoQuote;
	if (!(newtok = ft_dlstnew(&tokdat, sizeof(t_token))))
		return ;
	if (cpy_isalloced)
		free(cpy);
	ft_dlstpush(tokens, newtok);
	ft_tstrclr(vs);
}

static t_lexstate	get_nextstate(t_lexdat *dat)
{
	const t_equi		eq[] = {
	{kLexStateGeneral, &lex_general, (void*)dat},
	{kLexStateDQuote, &lex_dquote, (void*)dat},
	{kLexStateSQuote, &lex_squote, (void*)dat},
	{kLexStateAmpersand, &lex_ampersand, (void*)dat},
	{0, NULL, NULL}};
	const int			cmpdat = dat->curr_state;
	int					ret;

	ret = ft_switch((void*)&cmpdat, (void*)&eq, sizeof(t_equi), &ft_swcmp);
	return ((ret > 0) ? (t_lexstate)ret : kLexStateUndefined);
}

/*
** to be continued and normed
**
** How to manage lexer read-again?
** 	- special type for unfinished token?
**	- lexer automatically changes last token if lst isn't empty?
**
** 1. Add special type to last token if unfinished
** 2. When read again, lexer goes to last token and checks if unfinished, then changes
**		- to change, rm last token from dest and add it as current token
**		- to change, when add_token, check at that time and modify latest rather than add
**			- to save perf, only check once (store the result in t_lexdat)
*/

int					lex_line(t_dlist **dest, char *line)
{
	int			ret;
	t_lexdat	dat;

	if (!line || !dest)
		return (-1);
	ret = 1;
	*dest = NULL;
	ft_bzero(&dat, sizeof(t_lexdat));
	dat.currtoks = ft_tstrnew();
	dat.ret = dest;
	dat.curr_state = kLexStateGeneral;
	dat.linep = &line;
	while (*line != '#')
	{
		dat.jmp = get_charstate(&dat.cs, line);
		dat.curr_state = get_nextstate(&dat);
		if (!*line)
			break ;
		line += dat.jmp;
	}
	if (*dat.currtoks.s)
	{
		add_token(dat.ret, &dat.currtoks, WORD, 0);
		ret = 0;
	}
	ft_tstrdel(&dat.currtoks);
	return (ret);
}
