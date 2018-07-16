/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_semipipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 09:17:53 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/16 05:08:20 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

static void	create_tok_from_curr(void *data, t_toktype type, int prio)
{
	t_lexdat	*cdat;
	t_str		vdumb;
	char		tokc[2];

	if (!data)
		return ;
	cdat = (t_lexdat*)data;
	if (cdat->currtoks.s)
		add_token_to_ret(data);
	tokc[0] = **cdat->linep;
	tokc[1] = '\0';
	vdumb.s = tokc;
	add_token(cdat->ret, &vdumb, type, prio);
}

int			create_pipe_tok(void *data)
{
	create_tok_from_curr(data, PIPE, 1);
	return ((int)kLexStateGeneral);
}

int			create_semi_tok(void *data)
{
	create_tok_from_curr(data, SEMI, 2);
	return ((int)kLexStateGeneral);
}
