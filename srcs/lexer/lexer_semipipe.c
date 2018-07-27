/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_semipipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 09:17:53 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/27 04:30:43 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

static t_uint8	create_tok_from_curr(t_lexdat *cdat, t_toktype type, int prio)
{
	t_str		vs;

	if (cdat->currtoks.s && !add_token(cdat->ret, &cdat->currtoks, WORD, 0))
		return (FALSE);
	if (!ft_tstrnew(&vs) || !ft_tstrncpy(&vs, *cdat->linep, cdat->jmp)
		|| !add_token(cdat->ret, &vs, type, prio))
		return (FALSE);
	ft_tstrdel(&vs);
	return (TRUE);
}

int				create_pipe_tok(void *data)
{
	if (!create_tok_from_curr((t_lexdat*)data, PIPE, 1))
		return ((int)kLexStateUndefined);
	return ((int)kLexStateGeneral);
}

int				create_semi_tok(void *data)
{
	if (!create_tok_from_curr((t_lexdat*)data, SEMI, 2))
		return ((int)kLexStateUndefined);
	return ((int)kLexStateGeneral);
}
