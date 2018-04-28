/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ptrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 06:02:33 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/28 12:15:06 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "bl.h"

int		add_to_curr(void *data)
{
	const t_lexdat	*cdat = (t_lexdat*)data;

	ft_strnadd(cdat->currtokstr, (char*)&cdat->c, 1);
	return ((int)cdat->curr_state);
}

int		add_token_to_ret(void *data)
{
	const t_lexdat	*cdat = (t_lexdat*)data;

	add_token(cdat->ret, cdat->currtokstr);
	*cdat->currtokstr = ft_strnew(0);
	return ((int)cdat->curr_state);
}

int		switch_to_dquote(void *data)
{
	(void)data;
	return ((int)kLexStateDQuote);
}

int		switch_to_general(void *data)
{
	(void)data;
	return ((int)kLexStateGeneral);
}

int		ft_swcmp(void *p1, void *p2)
{
	const int	a = *(int*)p1;
	const int	b = *(int*)p2;

	return ((a == b));
}
