/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_great.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 14:10:56 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/26 09:27:03 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

void		add_io_nbr(t_lexdat *cdat)
{
	if (!cdat)
		return ;
	if (*cdat->currtoks)
	{
		if (!ft_strisnumeric(cdat->currtoks))
			add_token(cdat->ret, cdat->currtoks, WORD, 0);
		else
			add_token(cdat->ret, cdat->currtoks, IO_NUMBER, 0);
		free(cdat->currtoks);
		cdat->currtoks = ft_strnew(0);
	}
	ft_strnadd(&cdat->currtoks, &cdat->c, 1);
}

int			create_great_tok(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	add_io_nbr(cdat);
	add_token(cdat->ret, cdat->currtoks, GREAT, 0);
	free(cdat->currtoks);
	cdat->currtoks = ft_strnew(0);
	return ((int)kLexStateGeneral);
}

int			create_dgreat_tok(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	add_io_nbr(cdat);
	add_to_curr(data);
	add_token(cdat->ret, cdat->currtoks, DGREAT, 0);
	free(cdat->currtoks);
	cdat->currtoks = ft_strnew(0);
	return ((int)kLexStateGeneral);
}

/*
**static int	create_clobber_tok(void *data)
**{
**	t_lexdat	*cdat;
**
**	if (!data)
**		return ((int)kLexStateUndefined);
**	cdat = (t_lexdat*)data;
**	add_to_curr(data);
**	add_token(cdat->ret, cdat->currtoks, CLOBBER, 0);
**	free(cdat->currtoks);
**	cdat->currtoks = ft_strnew(0);
**	return ((int)kLexStateGeneral);
**}
**
**int			lex_great(void *data)
**{
**	t_charstate	cs;
**
**	if ((cs = ((t_lexdat*)data)->cs) == kCharGreat)
**	{
**		create_dgreat_tok(data);
**		return ((int)kLexStateGeneral);
**	}
**	if (cs == kCharPipe)
**	{
**		create_clobber_tok(data);
**		return ((int)kLexStateGeneral);
**	}
**	create_great_tok(data);
**	if (cs == kCharAmpersand)
**		return ((int)kLexStateAmpersand);
**	if (cs != kCharSpace)
**		add_to_curr(data);
**	return ((int)kLexStateGeneral);
**}
*/
