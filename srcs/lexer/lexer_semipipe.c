/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_semipipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 09:17:53 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/09 22:01:25 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

static t_uint8	create_tok_from_curr(t_lexdat *cdat, t_toktype type)
{
	t_str		vs;

	if (cdat->currtoks.s && !add_token(cdat->ret, &cdat->currtoks, WORD))
		return (FALSE);
	if (!ft_tstrnew(&vs) || !ft_tstrncpy(&vs, *cdat->linep, cdat->jmp)
		|| !add_token(cdat->ret, &vs, type))
		return (FALSE);
	ft_tstrdel(&vs);
	return (TRUE);
}

int				create_pipe_tok(void *data)
{
	if (!create_tok_from_curr((t_lexdat*)data, PIPE))
		return ((int)kLexStateUndefined);
	return ((int)kLexStateGeneral);
}

int				create_semi_tok(void *data)
{
	if (!create_tok_from_curr((t_lexdat*)data, SEMI))
		return ((int)kLexStateUndefined);
	return ((int)kLexStateGeneral);
}
