/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_switch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 23:11:41 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/18 21:13:40 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

int			ft_swcmp(void *p1, void *p2)
{
	const int	a = *(int*)p1;
	const int	b = *(int*)p2;

	return ((a == b));
}

/*
**int			switch_to_great(void *data)
**{
**	t_lexdat	*cdat;
**
**	if (!data)
**		return ((int)kLexStateUndefined);
**	cdat = (t_lexdat*)data;
**	if (*cdat->currtoks)
**	{
**		if (!ft_strisnumeric(cdat->currtoks))
**			add_token(cdat->ret, cdat->currtoks, WORD, 0);
**		else
**			add_token(cdat->ret, cdat->currtoks, IO_NUMBER, 0);
**		free(cdat->currtoks);
**		cdat->currtoks = ft_strnew(0);
**	}
**	add_to_curr(data);
**	return ((int)kLexStateGreat);
**}
**
**
**int			switch_to_less(void *data)
**{
**	switch_to_great(data);
**	return ((int)kLexStateLess);
**}
*/
