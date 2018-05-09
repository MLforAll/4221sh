/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 16:55:22 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/09 22:43:19 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../basiclexer/sh_lexer.h"

static t_btree	*create_cmd_node(t_list *tokens)
{
	t_btree	*ret;

	if (!(ret = ft_btnew(NULL, 0)))
		return (NULL);
	ret->data = (void*)tokens;
	return (ret);
}

static int		is_higher(t_list *token, t_list *top)
{
	t_token	*tokdat;
	t_token	*topdat;

	tokdat = (t_token*)token->content;
	if (tokdat->priority == 0)
		return (FALSE);
	if (!top)
		return (TRUE);
	topdat = (t_token*)top->content;
	return ((tokdat->type >= topdat->type));
}

t_btree			*parse_tokens(t_list *tokens)
{
	t_list	**top;
	t_list	**bw;
	t_list	*rtoks;
	t_btree	*ret;

	top = NULL;
	bw = &tokens;
	while (*bw)
	{
		if (is_higher(*bw, (top) ? *top : NULL))
			top = bw;
		bw = &(*bw)->next;
	}
	if (!top)
		return (create_cmd_node(tokens));
	rtoks = (*top)->next;
	*top = NULL;
	if (!(ret = ft_btnew("node", 4)))
		return (NULL);
	ft_btattach(ret, parse_tokens(tokens), parse_tokens(rtoks));
	return (ret);
}
