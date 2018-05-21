/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 17:10:58 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/21 17:26:37 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh_parser.h"

uint8_t		parser_check_syntax(t_list *tokens)
{
	t_token	*prev;
	t_token	*curr;

	prev = NULL;
	while (tokens)
	{
		curr = (t_token*)tokens->content;
		if (curr->type == PIPE && (!prev || prev->priority != 0))
			return (FALSE);
		prev = curr;
		tokens = tokens->next;
	}
	return (TRUE);
}
