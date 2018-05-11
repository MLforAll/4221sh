/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 19:30:28 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/11 23:26:08 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libftreadline.h"
#include "../../includes/sh_parser.h"

static void	do_stuff(char *line)
{
	t_list		*tokens;
	t_btree		*ast;

	if (!(tokens = lex_line(line)))
	{
		ft_putendl_fd("lexer error", STDERR_FILENO);
		return ;
	}
	ast = parse_tokens(tokens);
	ft_putubt(ast, &astputelem);
	ft_btdel(&ast, &ast_btdel);
	ft_lstdel(&tokens, &tokens_lstdel);
}

static void	read_loop(const char *pr, t_rl_opts *opts, t_rl_hist **hist)
{
	char		*line;
	int			limit;

	limit = 100;
	while ((line = ft_readline(pr, opts, *hist)))
	{
		if (*line)
		{
			do_stuff(line);
			if (--limit)
				ft_histadd(hist, line);
			else
			{
				ft_histdel(hist);
				limit = 100;
			}
		}
		free(line);
	}
}

int			main(void)
{
	const char	*pr = "\033[1;31mbasicparser\033[0;39m$ ";
	t_rl_opts	opts;
	t_rl_hist	*hist;

	ft_bzero(&opts, sizeof(t_rl_opts));
	opts.bell = YES;
	hist = NULL;
	read_loop(pr, &opts, &hist);
	ft_histdel(&hist);
	return (0);
}
