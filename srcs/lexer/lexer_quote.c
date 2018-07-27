/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 23:13:07 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/27 03:36:52 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_lexer.h"

int		lex_dquote(void *data)
{
	t_lexdat	*cdat;

	cdat = (t_lexdat*)data;
	if (lexact_append_current(data) == kLexStateUndefined)
		return ((int)kLexStateUndefined);
	if (cdat->cs == kCharDQuote)
		return ((int)kLexStateGeneral);
	if (cdat->cs == kCharEscape)
	{
		(*cdat->linep)++;
		if (lexact_append_current(data) == kLexStateUndefined)
			return ((int)kLexStateUndefined);
	}
	return ((int)kLexStateDQuote);
}

int		lex_squote(void *data)
{
	if (lexact_append_current(data) == kLexStateUndefined)
		return ((int)kLexStateUndefined);
	if (((t_lexdat*)data)->cs == kCharSQuote)
		return ((int)kLexStateGeneral);
	return ((int)kLexStateSQuote);
}

int		switch_to_dquote(void *data)
{
	if (lexact_append_current(data) == kLexStateUndefined)
		return ((int)kLexStateUndefined);
	return ((int)kLexStateDQuote);
}

int		switch_to_squote(void *data)
{
	if (lexact_append_current(data) == kLexStateUndefined)
		return ((int)kLexStateUndefined);
	return ((int)kLexStateSQuote);
}
