/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_less.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 14:10:56 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/23 03:20:41 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

int		create_less_tok(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	lexact_add_io_nbr(cdat);
	(void)lexact_append_current(data);
	add_token(cdat->ret, &cdat->currtoks, LESS, 0);
	return ((int)kLexStateRedirections);
}

int		create_dless_tok(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	lexact_add_io_nbr(cdat);
	(void)lexact_append_current(data);
	add_token(cdat->ret, &cdat->currtoks, DLESS, 0);
	return ((int)kLexStateRedirections);
}
