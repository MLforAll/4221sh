/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_great.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 14:10:56 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/08 23:21:38 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

static int	create_great_tok(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	add_token(cdat->ret, cdat->currtoks, GREAT);
	free(cdat->currtoks);
	cdat->currtoks = ft_strnew(0);
	return ((int)kLexStateGeneral);
}

static int	create_dgreat_tok(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	add_to_curr(data);
	add_token(cdat->ret, cdat->currtoks, DGREAT);
	free(cdat->currtoks);
	cdat->currtoks = ft_strnew(0);
	return ((int)kLexStateGeneral);
}

static int	create_clobber_tok(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	add_to_curr(data);
	add_token(cdat->ret, cdat->currtoks, CLOBBER);
	free(cdat->currtoks);
	cdat->currtoks = ft_strnew(0);
	return ((int)kLexStateGeneral);
}

int			lex_great(void *data)
{
	t_charstate	cs;

	cs = get_charstate(((t_lexdat*)data)->c);
	if (cs == kCharGreat)
	{
		create_dgreat_tok(data);
		return ((int)kLexStateGeneral);
	}
	if (cs == kCharPipe)
	{
		create_clobber_tok(data);
		return ((int)kLexStateGeneral);
	}
	create_great_tok(data);
	if (cs != kCharSpace)
		add_to_curr(data);
	return ((int)kLexStateGeneral);
}
