/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_dquote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 23:13:07 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/15 04:36:42 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_lexer.h"

int		lex_dquote(void *data)
{
	if (((t_lexdat*)data)->cs == kCharDQuote)
		return ((int)kLexStateGeneral);
	add_to_curr(data);
	return ((int)kLexStateDQuote);
}
