/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ampersand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 02:24:04 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/06 22:43:16 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

int			lex_redirects(void *data)
{
	t_lexdat	*cdat;

	if (!(cdat = (t_lexdat*)data))
		return ((int)kLexStateUndefined);
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

	if (!(cdat = (t_lexdat*)data))
		return ((int)kLexStateUndefined);
	if (cdat->cs == kCharDash && !*cdat->currtoks.s)
	{
		if (!create_token_with_buff(cdat, DASH))
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
	add_tok_ret = lexact_add_io_nbr(cdat);
	return ((int)((add_tok_ret) ? kLexStateGeneral : kLexStateUndefined));
}
