/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 14:10:56 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/09 22:01:20 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

static int		create_redir_tok(t_lexdat *cdat, t_toktype type)
{
	if (!lexact_add_io_nbr(cdat)
		|| lexact_append_current((void*)cdat) == kLexStateUndefined
		|| !add_token(cdat->ret, &cdat->currtoks, type))
		return ((int)kLexStateUndefined);
	return ((int)kLexStateRedirections);
}

int				create_great_tok(void *data)
{
	if (!data)
		return ((int)kLexStateUndefined);
	return (create_redir_tok((t_lexdat*)data, GREAT));
}

int				create_dgreat_tok(void *data)
{
	if (!data)
		return ((int)kLexStateUndefined);
	return (create_redir_tok((t_lexdat*)data, DGREAT));
}

int				create_less_tok(void *data)
{
	if (!data)
		return ((int)kLexStateUndefined);
	return (create_redir_tok((t_lexdat*)data, LESS));
}

int				create_dless_tok(void *data)
{
	if (!data)
		return ((int)kLexStateUndefined);
	return (create_redir_tok((t_lexdat*)data, DLESS));
}
