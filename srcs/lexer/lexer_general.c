/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 06:02:33 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/03 04:59:28 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

int			add_to_curr(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	(void)ft_tstrncat(&cdat->currtoks, cdat->linep, 1);
	return ((int)cdat->curr_state);
}

int			add_token_to_ret(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	add_token(cdat->ret, &cdat->currtoks, WORD, 0);
	return ((int)cdat->curr_state);
}

static int	switch_to_dquote(void *data)
{
	if (!add_to_curr(data))
		return ((int)kLexStateUndefined);
	return ((int)kLexStateDQuote);
}

int			lex_general(void *data)
{
	const t_equi		eq[] = {
	{kCharGeneral, &add_to_curr, (void*)data},
	{kCharDash, &add_to_curr, (void*)data},
	{kCharDQuote, &switch_to_dquote, (void*)data},
	{kCharSpace, &add_token_to_ret, (void*)data},
	{kCharNull, &add_token_to_ret, (void*)data},
	{kCharDGreat, &create_dgreat_tok, (void*)data},
	{kCharGreat, &create_great_tok, (void*)data},
	{kCharDLess, &create_dless_tok, (void*)data},
	{kCharLess, &create_less_tok, (void*)data},
	{kCharAmpersand, &switch_to_ampersand, (void*)data},
	{kCharPipe, &create_pipe_tok, (void*)data},
	{kCharSemi, &create_semi_tok, (void*)data},
	{0, NULL, NULL}};
	const t_charstate	cmpdat = ((t_lexdat*)data)->cs;

	return (ft_switch((void*)&cmpdat, (void*)&eq, sizeof(t_equi), &ft_swcmp));
}
