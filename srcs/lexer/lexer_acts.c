/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 21:09:20 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/06 05:32:45 by kdumarai         ###   ########.fr       */
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
	if (!add_token(cdat->ret, &cdat->currtoks, WORD))
		return ((int)kLexStateUndefined);
	return ((int)cdat->curr_state);
}

t_uint8		lexact_add_io_nbr(t_lexdat *cdat)
{
	if (!cdat || !*cdat->currtoks.s)
		return (TRUE);
	if (!ft_strisnumeric(cdat->currtoks.s))
		return (add_token(cdat->ret, &cdat->currtoks, WORD));
	return (add_token(cdat->ret, &cdat->currtoks, IO_NUMBER));
}

t_uint8		create_token_with_buff(t_lexdat *cdat, t_toktype type)
{
	t_str		vs;

	if (!ft_tstrnew(&vs) || !ft_tstrncpy(&vs, *cdat->linep, cdat->jmp)
		|| !add_token(cdat->ret, &vs, type))
		return (FALSE);
	ft_tstrdel(&vs);
	return (TRUE);
}
