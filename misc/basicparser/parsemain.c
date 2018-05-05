/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 16:55:22 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/05 17:37:21 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../basiclexer/bl.h"

static t_btree	*create_cmd_node(t_list *tokens)
{
	t_btree	*ret;

	if (!(ret = ft_btnew(NULL, 0)))
		return (NULL);
	ret->data = (void*)tokens;
	return (ret);
}

static int		is_rank(t_list *token)
{
	t_token	*tokdat;

	tokdat = (t_token*)token->content;
	/*if (tokdat->type == kTokTypePipe)
		return (TRUE);
	return (FALSE);*/
	return ((tokdat->type == kTokTypePipe));
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
		if (is_rank(*bw))
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
