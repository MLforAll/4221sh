/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ptrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 06:02:33 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/05 18:21:27 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "bl.h"

int		add_to_curr(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	ft_strnadd(&cdat->currtoks, &cdat->c, 1);
	return ((int)cdat->curr_state);
}

int		add_token_to_ret(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	add_token(cdat->ret, cdat->currtoks, kTokTypeGeneral);
	free(cdat->currtoks);
	cdat->currtoks = ft_strnew(0);
	return ((int)cdat->curr_state);
}

int		create_pipe_tok(void *data)
{
	t_lexdat	*cdat;
	char		pipec[2];

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	if (cdat->currtoks)
		add_token_to_ret(data);
	pipec[0] = cdat->c;
	pipec[1] = '\0';
	add_token(cdat->ret, pipec, kTokTypePipe);
	return ((int)cdat->curr_state);
}

int		switch_to_dquote(void *data)
{
	if (!add_to_curr(data))
		return ((int)kLexStateUndefined);
	return ((int)kLexStateDQuote);
}

int		switch_to_general(void *data)
{
	(void)data;
	return ((int)kLexStateGeneral);
}
