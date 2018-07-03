/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_less.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 14:10:56 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/03 04:58:50 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

int		create_less_tok(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	add_io_nbr(cdat);
	add_token(cdat->ret, &cdat->currtoks, LESS, 0);
	return ((int)kLexStateGeneral);
}

int		create_dless_tok(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	add_io_nbr(cdat);
	add_to_curr(data);
	add_token(cdat->ret, &cdat->currtoks, DLESS, 0);
	return ((int)kLexStateGeneral);
}

/*
**int			lex_less(void *data)
**{
**	t_charstate	cs;
**
**	if ((cs = ((t_lexdat*)data)->cs) == kCharLess)
**	{
**		create_dless_tok(data);
**		return ((int)kLexStateGeneral);
**	}
**	create_less_tok(data);
**	if (cs != kCharSpace)
**		add_to_curr(data);
**	return ((int)kLexStateGeneral);
**}
*/
