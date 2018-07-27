/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 21:09:20 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/27 05:29:39 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

int			lexact_append_current(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	if (!ft_tstrncat(&cdat->currtoks, *cdat->linep, cdat->jmp))
		return ((int)kLexStateUndefined);
	return ((int)cdat->curr_state);
}

int			lexact_add_token(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	if (!add_token(cdat->ret, &cdat->currtoks, WORD, 0))
		return ((int)kLexStateUndefined);
	return ((int)cdat->curr_state);
}

void		lexact_add_io_nbr(t_lexdat *cdat)
{
	if (!cdat)
		return ;
	if (*cdat->currtoks.s)
	{
		if (!ft_strisnumeric(cdat->currtoks.s))
			(void)add_token(cdat->ret, &cdat->currtoks, WORD, 0);
		else
			(void)add_token(cdat->ret, &cdat->currtoks, IO_NUMBER, 0);
	}
}

t_uint8		create_token_with_buff(t_lexdat *cdat, t_toktype type, int prio)
{
	t_str		vs;

	if (!ft_tstrnew(&vs) || !ft_tstrncpy(&vs, *cdat->linep, cdat->jmp)
		|| !add_token(cdat->ret, &vs, type, prio))
		return (FALSE);
	ft_tstrdel(&vs);
	return (TRUE);
}
