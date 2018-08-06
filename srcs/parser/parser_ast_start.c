/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast_start.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 16:55:22 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/06 22:27:55 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"

inline static t_btree	*create_cmd_node(t_dlist *tokens)
{
	t_btree		*ret;
	t_cmdnode	*cnode;
	t_astnode	ndat;

	ndat.type = 0;
	if (!(ndat.data = ft_memalloc(sizeof(t_cmdnode))))
		return (NULL);
	cnode = (t_cmdnode*)ndat.data;
	if (!(cnode->c_vars = ft_tabnew())
		|| !(cnode->c_av = ft_tabnew()))
	{
		cmdnode_free(cnode);
		return (NULL);
	}
	cnode->stdout_fd = -1;
	cnode->stdin_fd = -1;
	if (!fill_cmd_data(cnode, tokens)
		|| !(ret = ft_btnew(&ndat, sizeof(t_astnode))))
	{
		cmdnode_free(cnode);
		return (NULL);
	}
	return (ret);
}

inline static t_btree	*add_operator_leaf(t_dlist *tok)
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

inline t_uint8			is_twice_redir(t_dlist *atok)
{
	t_token	*nextdat;

	nextdat = atok->next ? (t_token*)atok->next->content : NULL;
	return (((t_token*)atok->content)->type == AMPERSAND && nextdat
			&& nextdat->type >= GREAT && nextdat->type <= DGREAT);
}

static int				is_higher(t_dlist *token, t_dlist *top)
{
	t_token	*tokdat;
	t_token	*nexdat;
	t_token	*topdat;

	tokdat = (t_token*)token->content;
	nexdat = token->next ? (t_token*)token->next->content : NULL;
	if (tokdat->type < PIPE || is_twice_redir(token))
		return (FALSE);
	if (!top)
		return (TRUE);
	topdat = (t_token*)top->content;
	return ((tokdat->type >= topdat->type));
}

t_btree					*parser_create_ast(t_dlist *tokens)
{
	t_dlist	**top;
	t_dlist	**bw;
	t_dlist	*bak;
	t_dlist	*rtoks;
	t_btree	*ret;

	top = NULL;
	bw = &tokens;
	while (*bw)
	{
		if (is_higher(*bw, (top) ? *top : NULL))
			top = bw;
		bw = &(*bw)->next;
	}
	if (!top && tokens)
		return (create_cmd_node(tokens));
	if (!tokens || !(ret = add_operator_leaf(*top)))
		return (NULL);
	rtoks = (*top)->next;
	bak = *top;
	*top = NULL;
	ft_btattach(ret, parser_create_ast(tokens), parser_create_ast(rtoks));
	*top = bak;
	return (ret);
}
