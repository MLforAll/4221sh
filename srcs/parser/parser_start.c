/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 16:55:22 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/21 23:31:55 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh_parser.h"

inline static t_btree	*create_cmd_node(t_list *tokens)
{
	t_btree		*ret;
	t_astnode	ndat;

	ndat.type = 0;
	ndat.data = ft_memalloc(sizeof(t_cmdnode));
	((t_cmdnode*)ndat.data)->c_av = ft_tabnew();
	((t_cmdnode*)ndat.data)->stdout_fd = -1;
	((t_cmdnode*)ndat.data)->stdin_fd = -1;
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

static t_btree			*parse_tokens_core(t_list *tokens)
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
	if (!top && tokens)
		return (create_cmd_node(tokens));
	if (!tokens || !(ret = add_operator_leaf(*top)))
		return (NULL);
	rtoks = (*top)->next;
	bak = *top;
	*top = NULL;
	ft_btattach(ret, parse_tokens_core(tokens), parse_tokens_core(rtoks));
	*top = bak;
	return (ret);
}

t_btree					*parse_tokens(char **line, t_list *tokens, uint8_t ra)
{
	uint8_t	chk_again;

	chk_again = TRUE;
	while (chk_again)
	{
		if (!parser_check_syntax(tokens, ra))
			return (NULL);
		parser_check_heredocs(tokens);
		chk_again = parser_check_inclist(line, &tokens);
	}
	return (parse_tokens_core(tokens));
}