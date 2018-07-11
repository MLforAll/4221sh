/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 17:10:58 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/11 04:30:56 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh_parser.h"

static char	*check_next_token(t_list *ntoken, t_toktype toktype)
{
	t_token	*ncurr;

	(void)toktype;
	if (!ntoken)
		return ("newline");
	ncurr = (t_token*)ntoken->content;
	if (ncurr->type != WORD && ncurr->type != AMPERSAND)
		return (ncurr->s);
	return (NULL);
}

char		*parser_check_syntax(t_list *tokens)
{
	t_token	*prev;
	t_token	*curr;
	char	*tmp;

	prev = NULL;
	while (tokens)
	{
		curr = (t_token*)tokens->content;
		if (curr->type == PIPE && (!prev || prev->priority != 0))
			return (curr->s);
		if (curr->type >= GREAT && curr->type <= DLESS
			&& (tmp = check_next_token(tokens->next, WORD)))
			return (tmp);
		prev = curr;
		tokens = tokens->next;
	}
	return (NULL);
}
