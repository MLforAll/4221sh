/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 06:02:33 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/01 19:43:40 by kdumarai         ###   ########.fr       */
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
			&& !add_token(cdat->ret, &cdat->currtoks, INCOMPG, 0))
			return ((int)kLexStateUndefined);
		return ((int)kLexStateReadAgain);
	}
	if (lexact_append_current(data) == kLexStateUndefined)
		return ((int)kLexStateUndefined);
	return ((int)cdat->curr_state);
}

static int	create_ampersand(void *data)
{
	if (!create_token_with_buff((t_lexdat*)data, AMPERSAND, 1))
		return ((int)kLexStateUndefined);
	return ((int)((t_lexdat*)data)->curr_state);
}

static int	create_andif(void *data)
{
	if (!create_token_with_buff((t_lexdat*)data, AND_IF, 1))
		return ((int)kLexStateUndefined);
	return ((int)((t_lexdat*)data)->curr_state);
}

static int	create_orif(void *data)
{
	if (!create_token_with_buff((t_lexdat*)data, OR_IF, 1))
		return ((int)kLexStateUndefined);
	return ((int)((t_lexdat*)data)->curr_state);
}

int			lex_general(void *data)
{
	const t_equi		eq[] = {
	{kCharGeneral, &lexact_append_current, (void*)data, "\0"},
	{kCharDash, &lexact_append_current, (void*)data, "\0"},
	{kCharDQuote, &switch_to_dquote, (void*)data, "\0"},
	{kCharSQuote, &switch_to_squote, (void*)data, "\0"},
	{kCharEscape, &create_escape, (void*)data, "\0"},
	{kCharSpace, &lexact_add_token, (void*)data, "\0"},
	{kCharTab, &lexact_add_token, (void*)data, "\0"},
	{kCharNull, &lexact_add_token, (void*)data, "\0"},
	{kCharDGreat, &create_dgreat_tok, (void*)data, "\0"},
	{kCharGreat, &create_great_tok, (void*)data, "\0"},
	{kCharDLess, &create_dless_tok, (void*)data, "\0"},
	{kCharLess, &create_less_tok, (void*)data, "\0"},
	{kCharAmpersand, &create_ampersand, (void*)data, "\0"},
	{kCharAndIf, &create_andif, (void*)data, "\0"},
	{kCharOrIf, &create_orif, (void*)data, "\0"},
	{kCharPipe, &create_pipe_tok, (void*)data, "\0"},
	{kCharSemi, &create_semi_tok, (void*)data, "\0"},
	{0, NULL, NULL, "\0"}};
	const t_charstate	cmpdat = ((t_lexdat*)data)->cs;

	return (ft_switch((void*)&cmpdat, (void*)&eq, sizeof(t_equi), &ft_swcmp));
}
