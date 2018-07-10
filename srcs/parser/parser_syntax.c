/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 17:10:58 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/10 22:54:53 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh_parser.h"

t_uint8		parser_check_syntax(t_list *tokens, t_uint8 ragain)
{
	t_token	*prev;
	t_token	*curr;

	(void)ragain;
	prev = NULL;
	while (tokens)
	{
		curr = (t_token*)tokens->content;
		if (curr->type == PIPE && (!prev || prev->priority != 0))
			return (FALSE);
		if (curr->type >= GREAT && curr->type <= DLESS && (!tokens->next
			|| (((t_token*)tokens->next->content)->type != WORD
				&& ((t_token*)tokens->next->content)->type != AMPERSAND)))
			return (FALSE);
		prev = curr;
		tokens = tokens->next;
	}
	return (TRUE);
}
