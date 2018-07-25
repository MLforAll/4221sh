/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 21:09:20 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/25 04:12:03 by kdumarai         ###   ########.fr       */
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
	(void)ft_tstrncat(&cdat->currtoks, *cdat->linep, cdat->jmp);
	return ((int)cdat->curr_state);
}

int			lexact_add_token(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	(void)add_token(cdat->ret, &cdat->currtoks, WORD, 0);
	return ((int)cdat->curr_state);
}

void		lexact_add_io_nbr(t_lexdat *cdat)
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
}

void		create_token_with_buff(t_lexdat *cdat, t_toktype type, int prio)
{
	t_str		vs;

	(void)ft_tstrnew(&vs);
	(void)ft_tstrncpy(&vs, *cdat->linep, cdat->jmp);
	add_token(cdat->ret, &vs, type, prio);
	ft_tstrdel(&vs);
}
