/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_semipipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 09:17:53 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/18 21:07:16 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

static void	create_tok_from_curr(t_lexdat *cdat, t_toktype type, int prio)
{
	t_str		vdumb;

	if (cdat->currtoks.s)
		(void)add_token(cdat->ret, &cdat->currtoks, WORD, 0);
	vdumb = ft_tstrnew();
	ft_tstrncpy(&vdumb, *cdat->linep, cdat->jmp);
	add_token(cdat->ret, &vdumb, type, prio);
	ft_tstrdel(&vdumb);
}

int			create_pipe_tok(void *data)
{
	create_tok_from_curr((t_lexdat*)data, PIPE, 1);
	return ((int)kLexStateGeneral);
}

int			create_semi_tok(void *data)
{
	create_tok_from_curr((t_lexdat*)data, SEMI, 2);
	return ((int)kLexStateGeneral);
}
