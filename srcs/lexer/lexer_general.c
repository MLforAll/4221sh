/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 06:02:33 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/21 06:08:10 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

static int	switch_to_dquote(void *data)
{
	lexact_append_current(data);
	return ((int)kLexStateDQuote);
}

static int	switch_to_squote(void *data)
{
	lexact_append_current(data);
	return ((int)kLexStateSQuote);
}

int			lex_general(void *data)
{
	const t_equi		eq[] = {
	{kCharGeneral, &lexact_append_current, (void*)data},
	{kCharDash, &lexact_append_current, (void*)data},
	{kCharDQuote, &switch_to_dquote, (void*)data},
	{kCharSQuote, &switch_to_squote, (void*)data},
	{kCharSpace, &lexact_add_token, (void*)data},
	{kCharTab, &lexact_add_token, (void*)data},
	{kCharNull, &lexact_add_token, (void*)data},
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
