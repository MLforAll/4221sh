/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 23:44:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/17 02:08:30 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_parser.h"
#include "libftreadline.h"

static char	*read_till_delim(char *delim)
{
	char		*ret;
	char		*line;
	t_rl_opts	opts;

	ret = ft_strnew(0);
	ft_bzero(&opts, sizeof(t_rl_opts));
	line = NULL;
	while (TRUE)
	{
		if (!(line = ft_readline("> ", &opts, NULL))
			|| ft_strequ(line, delim))
			break ;
		ft_stradd(&ret, line);
		ft_stradd(&ret, "\n");
		ft_strdel(&line);
	}
	free(delim);
	return (ret);
}

void	parser_check_heredocs(t_list *tokens)
{
	char	**toks_dest;

	while (tokens)
	{
		if (((t_token*)tokens->content)->type == DLESS
			&& tokens->next->content
			&& ((t_token*)tokens->next->content)->type == WORD)
		{
			toks_dest = &((t_token*)tokens->next->content)->toks;
			*toks_dest = read_till_delim(*toks_dest);
		}
		tokens = tokens->next;
	}
}
