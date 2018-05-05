/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 14:10:56 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/05 18:22:09 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "bl.h"

int		create_redir_tok(void *data)
{
	t_lexdat	*cdat;
	char		redirc[2];

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	if (*cdat->currtoks)
	{
		if (!ft_strisnumeric(cdat->currtoks))
		{
			add_token(cdat->ret, cdat->currtoks, kTokTypeGeneral);
			add_token(cdat->ret, "1", kTokTypeIONumber);
		}
		else
			add_token(cdat->ret, cdat->currtoks, kTokTypeIONumber);
		free(cdat->currtoks);
		cdat->currtoks = ft_strnew(0);
	}
	redirc[0] = cdat->c;
	redirc[1] = '\0';
	add_token(cdat->ret, redirc, kTokTypeRedir);
	return ((int)kLexStateGeneral);
}
