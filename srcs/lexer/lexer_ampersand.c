/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ampersand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 02:24:04 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/18 05:26:12 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

static int	create_dash_tok(void *data)
{
	t_lexdat	*cdat;
	char		tokc[2];
	t_str		vdumb;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	tokc[0] = **cdat->linep;
	tokc[1] = '\0';
	vdumb.s = tokc;
	(void)add_token(cdat->ret, &vdumb, DASH, 0);
	return ((int)kLexStateGeneral);
}

int			lex_ampersand(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	if (cdat->cs == kCharDash && !*cdat->currtoks.s)
		return (create_dash_tok(data));
	if (cdat->cs != kCharSpace && cdat->cs != kCharNull)
	{
		(void)lex_general(data);
		return ((int)kLexStateAmpersand);
	}
	if (!ft_strisnumeric(cdat->currtoks.s))
		add_token(cdat->ret, &cdat->currtoks, WORD, 0);
	else
		add_token(cdat->ret, &cdat->currtoks, IO_NUMBER, 0);
	return ((int)kLexStateGeneral);
}
