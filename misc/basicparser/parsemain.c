/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 16:55:22 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/11 19:23:09 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "bp.h"

inline static t_btree	*create_cmd_node(t_list *tokens)
{
	t_btree		*ret;
	t_astnode	ndat;

	ndat.type = 0;
	ndat.data = ft_memalloc(sizeof(t_cmdnode));
	fill_cmd_data((t_cmdnode*)ndat.data, tokens);
	if (!(ret = ft_btnew(&ndat, sizeof(t_astnode))))
		return (NULL);
	return (ret);
}

inline static t_btree	*add_operator_leaf(t_list *tok)
{
	t_btree		*ret;
	t_astnode	ndat;

	if (!tok)
		return (NULL);
	ndat.data = NULL;
	ndat.type = ((t_token*)tok->content)->type;
	if (!(ret = ft_btnew(&ndat, sizeof(ndat))))
		return (NULL);
	return (ret);
}

static int				is_higher(t_list *token, t_list *top)
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

t_btree					*parse_tokens(t_list *tokens)
{
	t_list	**top;
	t_list	**bw;
	t_list	*bak;
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
	if (!(ret = add_operator_leaf(*top)))
		return (NULL);
	rtoks = (*top)->next;
	bak = *top;
	*top = NULL;
	ft_btattach(ret, parse_tokens(tokens), parse_tokens(rtoks));
	*top = bak;
	return (ret);
}
