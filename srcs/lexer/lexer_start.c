/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 20:14:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/25 04:11:16 by kdumarai         ###   ########.fr       */
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
	const char			*chars[] = {">>", ">", "<<", "<", "&&", "||", "&", "-",
									";", "|", "\"", "'", "\\", " ", "\t"};
	const t_charstate	st[] = {kCharDGreat, kCharGreat, kCharDLess, kCharLess,
							kCharAndIf, kCharOrIf, kCharAmpersand, kCharDash,
							kCharSemi, kCharPipe, kCharDQuote, kCharSQuote,
							kCharEscape, kCharSpace, kCharTab};

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
		idx++;
	}
	*cs = kCharGeneral;
	return (1);
}

static t_lexstate	get_nextstate(t_lexdat *dat)
{
	const t_equi		eq[] = {
	{kLexStateGeneral, &lex_general, (void*)dat},
	{kLexStateDQuote, &lex_dquote, (void*)dat},
	{kLexStateSQuote, &lex_squote, (void*)dat},
	{kLexStateAmpersand, &lex_ampersand, (void*)dat},
	{kLexStateRedirections, &lex_redirects, (void*)dat},
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
**	- lexer automatically changes last token if lst is not empty?
**
** 1. Add special type to last token if unfinished
** 2. When read again, lexer goes to last token and checks if unfinished,
**			then changes
**		- to change, rm last token from dest and add it as current token
**		- to change, when add_token, check at that time and modify latest
**			rather than add
**			- to save perf, only check once (store the result in t_lexdat)
*/

static void			lex_init(t_dlist **lst, t_lexdat *cdat, char **line)
{
	t_toktype	type;

	ft_bzero(cdat, sizeof(t_lexdat));
	cdat->ret = lst;
	cdat->linep = line;
	(void)ft_tstrnew(&cdat->currtoks);
	cdat->curr_state = kLexStateGeneral;
	if (!*lst)
		return ;
	while ((*lst)->next)
		lst = &(*lst)->next;
	type = ((t_token*)(*lst)->content)->type;
	if (type >= INCOMPG && type <= INCOMPS)
	{
		cdat->curr_state = (t_lexstate)(type + 1);
		ft_tstrcpy(&cdat->currtoks, ((t_token*)(*lst)->content)->s);
		ft_dlstdelone(lst, &tokens_lstdel);
	}
}

int					lex_line(t_dlist **dest, char *line)
{
	int			ret;
	t_lexdat	dat;

	if (!line || !dest)
		return (LEXER_FAIL);
	ret = LEXER_OK;
	lex_init(dest, &dat, &line);
	while (*line != '#')
	{
		dat.jmp = get_charstate(&dat.cs, line);
		if ((dat.curr_state = get_nextstate(&dat)) == kLexStateReadAgain)
			ret = LEXER_INC;
		if (!*line)
			break ;
		line += dat.jmp;
	}
	if (*dat.currtoks.s)
	{
		add_token(dat.ret, &dat.currtoks,
				(dat.curr_state == kLexStateDQuote) ? INCOMPD : INCOMPS, 0);
		ret = (dat.curr_state == kLexStateDQuote) ? LEXER_INCDQ : LEXER_INCSQ;
	}
	ft_tstrdel(&dat.currtoks);
	return (ret);
}
