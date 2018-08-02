/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 23:44:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/02 18:50:49 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"

static void		expand_heredoc_data(char **fetch)
{
	t_str	vs;
	char	*tmp;

	if (!ft_tstrnew(&vs))
		return ;
	tmp = *fetch;
	while (*tmp)
	{
		if ((*tmp != '$' || !lexer_expand_getvar(&tmp, &vs))
			&& !ft_tstrncat(&vs, tmp, 1))
		{
			ft_tstrdel(&vs);
			return ;
		}
		tmp++;
	}
	free(*fetch);
	*fetch = vs.s;
}

/*
** todo: if tmp == NULL, output error?
*/

int				parser_check_heredocs(t_dlist *tokens, int fd)
{
	t_token			*tok;
	char			**toks_dest;
	char			*tmp;
	struct s_raconf	conf;

	tok = (t_token*)tokens->content;
	if (tok->type != DLESS)
		return (FALSE);
	if (!tokens->next || !tokens->next->content)
		return (-1);
	if (((t_token*)tokens->next->content)->type == WORD)
	{
		toks_dest = &((t_token*)tokens->next->content)->s;
		get_raconf(&conf, SH_HEREDOC_PR, *toks_dest, RACONF_PPL | RACONF_BELL);
		if (!(tmp = read_till_delim(&conf, RA_WHOLE, fd))
			&& !(tmp = ft_strnew(0)))
			return (FALSE);
		else if (ft_strchr(tmp, '$'))
			expand_heredoc_data(&tmp);
		free(*toks_dest);
		*toks_dest = tmp;
		return (TRUE);
	}
	return (FALSE);
}
