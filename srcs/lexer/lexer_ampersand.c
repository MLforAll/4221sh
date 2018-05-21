/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ampersand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 02:24:04 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/21 23:33:18 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

static int	create_dash_tok(void *data)
{
	t_lexdat	*cdat;
	char		tokc[2];

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	tokc[0] = cdat->c;
	tokc[1] = '\0';
	add_token(cdat->ret, tokc, DASH, 0);
	return ((int)kLexStateGeneral);
}

int			lex_ampersand(void *data)
{
	t_charstate	cs;
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	if ((cs = get_charstate(cdat->c)) == kCharDash && !*cdat->currtoks)
		return (create_dash_tok(data));
	if (cs != kCharSpace && cs != kCharNull)
	{
		lex_general(data);
		return ((int)kLexStateAmpersand);
	}
	if (!ft_strisnumeric(cdat->currtoks))
		add_token(cdat->ret, cdat->currtoks, WORD, 0);
	else
		add_token(cdat->ret, cdat->currtoks, IO_NUMBER, 0);
	free(cdat->currtoks);
	cdat->currtoks = ft_strnew(0);
	return ((int)kLexStateGeneral);
}
