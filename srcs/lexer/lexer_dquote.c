/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_dquote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 23:13:07 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/13 02:02:46 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_lexer.h"

int		lex_dquote(void *data)
{
	add_to_curr(data);
	if (get_charstate(((t_lexdat*)data)->c) == kCharDQuote)
		return ((int)kLexStateGeneral);
	return ((int)kLexStateDQuote);
}
