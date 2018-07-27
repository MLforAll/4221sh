/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_great.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 14:10:56 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/27 04:18:12 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

int			create_great_tok(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	lexact_add_io_nbr(cdat);
	if (lexact_append_current(data) == kLexStateUndefined
		|| !add_token(cdat->ret, &cdat->currtoks, GREAT, 0))
		return ((int)kLexStateUndefined);
	return ((int)kLexStateRedirections);
}

int			create_dgreat_tok(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	lexact_add_io_nbr(cdat);
	if (lexact_append_current(data) == kLexStateUndefined
		|| !add_token(cdat->ret, &cdat->currtoks, DGREAT, 0))
		return ((int)kLexStateUndefined);
	return ((int)kLexStateRedirections);
}
