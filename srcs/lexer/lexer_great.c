/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_great.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 14:10:56 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/18 19:14:07 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

void		add_io_nbr(t_lexdat *cdat)
{
	if (!cdat)
		return ;
	if (*cdat->currtoks.s)
	{
		if (!ft_strisnumeric(cdat->currtoks.s))
			add_token(cdat->ret, &cdat->currtoks, WORD, 0);
		else
			add_token(cdat->ret, &cdat->currtoks, IO_NUMBER, 0);
	}
	//ft_tstrncat(&cdat->currtoks, *cdat->linep, 1);
}

int			create_great_tok(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	add_io_nbr(cdat);
	(void)add_to_curr(data);
	add_token(cdat->ret, &cdat->currtoks, GREAT, 0);
	return ((int)kLexStateGeneral);
}

int			create_dgreat_tok(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	add_io_nbr(cdat);
	(void)add_to_curr(data);
	add_token(cdat->ret, &cdat->currtoks, DGREAT, 0);
	return ((int)kLexStateGeneral);
}
