/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 06:02:33 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/09 22:00:59 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

static int	create_escape(void *data)
{
	t_lexdat	*cdat;

	cdat = (t_lexdat*)data;
	if (ft_strstart(*cdat->linep, "\\\\"))
	{
		if (lexact_append_current(data) == kLexStateUndefined)
			return ((int)kLexStateUndefined);
		*cdat->linep += 2;
		return ((int)cdat->curr_state);
	}
	if ((*cdat->linep)[1] == '\0')
	{
		if (*cdat->currtoks.s
			&& !add_token(cdat->ret, &cdat->currtoks, INCOMPG))
			return ((int)kLexStateUndefined);
		return ((int)kLexStateReadAgain);
	}
	if (lexact_append_current(data) == kLexStateUndefined)
		return ((int)kLexStateUndefined);
	(*cdat->linep)++;
	if (lexact_append_current(data) == kLexStateUndefined)
		return ((int)kLexStateUndefined);
	return ((int)cdat->curr_state);
}

static int	create_ampersand(void *data)
{
	if (!create_token_with_buff((t_lexdat*)data, AMPERSAND))
		return ((int)kLexStateUndefined);
	return ((int)((t_lexdat*)data)->curr_state);
}

static int	create_andif(void *data)
{
	if (*((t_lexdat*)data)->currtoks.s
		&& lexact_add_token(data) == kLexStateUndefined)
		return ((int)kLexStateUndefined);
	if (!create_token_with_buff((t_lexdat*)data, AND_IF))
		return ((int)kLexStateUndefined);
	return ((int)((t_lexdat*)data)->curr_state);
}

static int	create_orif(void *data)
{
	if (*((t_lexdat*)data)->currtoks.s
		&& lexact_add_token(data) == kLexStateUndefined)
		return ((int)kLexStateUndefined);
	if (!create_token_with_buff((t_lexdat*)data, OR_IF))
		return ((int)kLexStateUndefined);
	return ((int)((t_lexdat*)data)->curr_state);
}

int			lex_general(void *data)
{
	const t_equi		eq[] = {
	{kCharGeneral, "\0", &lexact_append_current, (void*)data},
	{kCharDash, "\0", &lexact_append_current, (void*)data},
	{kCharDQuote, "\0", &switch_to_dquote, (void*)data},
	{kCharSQuote, "\0", &switch_to_squote, (void*)data},
	{kCharEscape, "\0", &create_escape, (void*)data},
	{kCharSpace, "\0", &lexact_add_token, (void*)data},
	{kCharTab, "\0", &lexact_add_token, (void*)data},
	{kCharNull, "\0", &lexact_add_token, (void*)data},
	{kCharDGreat, "\0", &create_dgreat_tok, (void*)data},
	{kCharGreat, "\0", &create_great_tok, (void*)data},
	{kCharDLess, "\0", &create_dless_tok, (void*)data},
	{kCharLess, "\0", &create_less_tok, (void*)data},
	{kCharAmpersand, "\0", &create_ampersand, (void*)data},
	{kCharAndIf, "\0", &create_andif, (void*)data},
	{kCharOrIf, "\0", &create_orif, (void*)data},
	{kCharPipe, "\0", &create_pipe_tok, (void*)data},
	{kCharSemi, "\0", &create_semi_tok, (void*)data},
	{0, "\0", NULL, NULL}};
	const t_charstate	cmpdat = ((t_lexdat*)data)->cs;

	return (ft_switch((const void*)&cmpdat, (const void*)&eq, \
			sizeof(t_equi), &ft_swcmp));
}
