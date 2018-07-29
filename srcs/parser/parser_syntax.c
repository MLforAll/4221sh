/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 17:10:58 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/29 01:37:42 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh_parser.h"

static char	*check_next_token(t_dlist *ntoken, t_toktype toktype)
{
	t_token	*ncurr;

	if (!ntoken)
		return ("newline");
	ncurr = (t_token*)ntoken->content;
	if (ncurr->type != toktype)
		return (ncurr->s);
	return (NULL);
}

char		*parser_check_syntax(t_dlist *tokens)
{
	t_token	*prev;
	t_token	*curr;
	char	*tmp;

	curr = (t_token*)tokens->content;
	prev = (tokens->prev) ? (t_token*)tokens->prev->content : NULL;
	if (curr->type == SEMI && (!prev || prev->type >= PIPE))
		return (curr->s);
	if (curr->type == PIPE && (!prev || !tokens->next || prev->priority != 0))
		return (curr->s);
	if (curr->type >= GREAT && curr->type <= DLESS
		&& (tmp = check_next_token(tokens->next, WORD))
		&& (tmp = check_next_token(tokens->next, DASH))
		&& (tmp = check_next_token(tokens->next, IO_NUMBER)))
		return (tmp);
	prev = curr;
	tokens = tokens->next;
	return (NULL);
}
