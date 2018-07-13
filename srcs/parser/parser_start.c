/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 16:55:22 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/13 05:33:34 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"

inline static t_btree	*create_cmd_node(t_list *tokens)
{
	t_btree		*ret;
	t_astnode	ndat;

	ndat.type = 0;
	ndat.data = ft_memalloc(sizeof(t_cmdnode));
	((t_cmdnode*)ndat.data)->c_vars = ft_tabnew();
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

t_btree					*parse_tokens(char **line, t_list *tokens)
{
	t_uint8	changes;
	char	*syntax_err;

	changes = FALSE;
	while (!changes)
	{
		if ((syntax_err = parser_check_syntax(tokens)))
		{
			ft_putstr_fd(g_sh_name, STDERR_FILENO);
			ft_putstr_fd(": syntax error near unexpected token `", STDERR_FILENO);
			ft_putstr_fd(syntax_err, STDERR_FILENO);
			ft_putendl_fd("`", STDERR_FILENO);
			return (NULL);
		}
		changes |= parser_check_heredocs(tokens, (line != NULL));
		changes |= parser_check_inclist(line, &tokens);
		if (changes && !line)
		{
			ft_putendl_fd("Interactive mode not enabled!", STDERR_FILENO);
			return (NULL);
		}
	}
	return (parse_tokens_core(tokens));
}
