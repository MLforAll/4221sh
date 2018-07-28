/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ampersand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 02:24:04 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/28 17:38:45 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

int			lex_redirects(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	if (cdat->cs == kCharAmpersand)
		return ((int)kLexStateAmpersand);
	if (lex_general(data) == kLexStateUndefined)
		return ((int)kLexStateUndefined);
	return ((int)kLexStateGeneral);
}

int			lex_ampersand(void *data)
{
	t_lexdat	*cdat;
	t_uint8		add_tok_ret;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	if (cdat->cs == kCharDash && !*cdat->currtoks.s)
	{
		if (!create_token_with_buff(cdat, DASH, 0))
			return ((int)kLexStateUndefined);
		return ((int)kLexStateGeneral);
	}
	if (cdat->cs != kCharSpace && cdat->cs != kCharAmpersand
		&& cdat->cs != kCharNull)
	{
		if (lex_general(data) == kLexStateUndefined)
			return ((int)kLexStateUndefined);
		return ((int)kLexStateAmpersand);
	}
	if (!ft_strisnumeric(cdat->currtoks.s))
		add_tok_ret = add_token(cdat->ret, &cdat->currtoks, WORD, 0);
	else
		add_tok_ret = add_token(cdat->ret, &cdat->currtoks, IO_NUMBER, 0);
	return ((int)((add_tok_ret) ? kLexStateAmpersand : kLexStateUndefined));
}
