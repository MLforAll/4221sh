/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 20:14:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/30 21:46:00 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

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
	return ((t_lexstate)ret);
}

static t_uint8		lex_init(t_dlist **lst, t_lexdat *cdat, char **line)
{
	t_toktype	type;

	ft_bzero(cdat, sizeof(t_lexdat));
	cdat->ret = lst;
	cdat->linep = line;
	if (!ft_tstrnew(&cdat->currtoks))
		return (FALSE);
	cdat->curr_state = kLexStateGeneral;
	if (!*lst)
		return (TRUE);
	while ((*lst)->next)
		lst = &(*lst)->next;
	type = ((t_token*)(*lst)->content)->type;
	if (type >= INCOMPG && type <= INCOMPS)
	{
		cdat->curr_state = (t_lexstate)(type + 1);
		if (!ft_tstrcpy(&cdat->currtoks, ((t_token*)(*lst)->content)->s))
			return (FALSE);
		ft_dlstdelone(lst, &tokens_lstdel);
	}
	return (TRUE);
}

static int			lex_deinit(t_lexdat *cdat, int ret)
{
	t_lexstate	state;

	if (cdat->curr_state == kLexStateDQuote
		|| cdat->curr_state == kLexStateSQuote)
	{
		if (!add_token(cdat->ret, &cdat->currtoks, \
				(cdat->curr_state == kLexStateDQuote) ? INCOMPD : INCOMPS, 0))
			return (LEXER_FAIL);
		state = cdat->curr_state;
		return ((state == kLexStateDQuote) ? LEXER_INCDQ : LEXER_INCSQ);
	}
	if (*cdat->currtoks.s
		&& lexact_add_token((void*)cdat) == kLexStateUndefined)
		return (LEXER_FAIL);
	return (ret);
}

int					lex_line(t_dlist **dest, char *line)
{
	int			ret;
	t_lexdat	dat;

	if (!line || !dest || !lex_init(dest, &dat, &line))
		return (LEXER_FAIL);
	ret = LEXER_OK;
	while (*line != '#')
	{
		dat.jmp = get_charstate(&dat.cs, line);
		if ((dat.curr_state = get_nextstate(&dat)) == kLexStateReadAgain)
			ret = LEXER_INC;
		if (!*line || dat.curr_state == kLexStateUndefined)
			break ;
		line += dat.jmp;
	}
	if ((ret = lex_deinit(&dat, ret)) == LEXER_FAIL)
		ft_dlstdel(dest, &tokens_lstdel);
	ft_tstrdel(&dat.currtoks);
	return (ret);
}
