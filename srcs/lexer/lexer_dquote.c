/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_dquote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 23:13:07 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/18 05:25:39 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_lexer.h"

int		lex_dquote(void *data)
{
	t_lexdat	*cdat;

	cdat = (t_lexdat*)data;
	if (cdat->cs == kCharDQuote)
		return ((int)kLexStateGeneral);
	if (cdat->cs == kCharEscape)
		(*cdat->linep)++;
	(void)add_to_curr(data);
	return ((int)kLexStateDQuote);
}

int		lex_squote(void *data)
{
	if (((t_lexdat*)data)->cs == kCharSQuote)
		return ((int)kLexStateGeneral);
	(void)add_to_curr(data);
	return ((int)kLexStateSQuote);
}
