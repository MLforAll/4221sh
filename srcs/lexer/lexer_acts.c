/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 21:09:20 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/19 06:19:45 by kdumarai         ###   ########.fr       */
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
		if (cdat->currtok_quoting != kNoQuote
			|| !ft_strisnumeric(cdat->currtoks.s))
			add_token(cdat->ret, &cdat->currtoks, WORD, 0);
		else
			add_token(cdat->ret, &cdat->currtoks, IO_NUMBER, 0);
	}
}

/*
** 4 args -> problem -> no info on quoting
** Solutions:
**	1. rm priority, add a func to parser
**	2. have a custom t_currtok struct in lexdat_t and pass it instead of vs, type and prio
*/

void				add_token(t_dlist **tokens,
							t_str *vs,
							t_toktype type,
							int prio)
{
	t_dlist	*newtok;
	t_token	tokdat;
	char	*cpy;
	int		cpy_isalloced;

	if (!vs || (ft_strlen(vs->s) < 1))
		return ;
	ft_bzero(&tokdat, sizeof(t_token));
	cpy = vs->s;
	cpy_isalloced = (lexer_expand_tilde(&cpy) || lexer_expand_var(&cpy));
	if (!(tokdat.s = ft_strdup(cpy)))
		return ;
	tokdat.type = type;
	tokdat.priority = prio;
	tokdat.quoting = kNoQuote;
	if (!(newtok = ft_dlstnew(&tokdat, sizeof(t_token))))
		return ;
	if (cpy_isalloced)
		free(cpy);
	ft_dlstpush(tokens, newtok);
	ft_tstrclr(vs);
}
