/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 06:02:33 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/09 22:28:51 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

int			add_to_curr(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	ft_strnadd(&cdat->currtoks, &cdat->c, 1);
	return ((int)cdat->curr_state);
}

int			add_token_to_ret(void *data)
{
	t_lexdat	*cdat;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	add_token(cdat->ret, cdat->currtoks, WORD, 0);
	free(cdat->currtoks);
	cdat->currtoks = ft_strnew(0);
	return ((int)cdat->curr_state);
}

static int	create_pipe_tok(void *data)
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
	add_token(cdat->ret, pipec, PIPE, 1);
	return ((int)cdat->curr_state);
}

static int	switch_to_dquote(void *data)
{
	if (!add_to_curr(data))
		return ((int)kLexStateUndefined);
	return ((int)kLexStateDQuote);
}

int			lex_general(void *data)
{
	const t_equi		eq[7] = {
	{kCharGeneral, &add_to_curr, (void*)data},
	{kCharDQuote, &switch_to_dquote, (void*)data},
	{kCharSpace, &add_token_to_ret, (void*)data},
	{kCharGreat, &switch_to_great, (void*)data},
	{kCharLess, &switch_to_less, (void*)data},
	{kCharPipe, &create_pipe_tok, (void*)data},
	{0, NULL, NULL}};
	const t_charstate	cmpdat = get_charstate(((t_lexdat*)data)->c);

	return (ft_switch((void*)&cmpdat, (void*)&eq, sizeof(t_equi), &ft_swcmp));
}
