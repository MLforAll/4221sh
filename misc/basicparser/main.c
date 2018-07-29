/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 19:30:28 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/29 17:51:28 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libftreadline.h"
#include "bpintern.h"
#include "../../includes/sh_parser.h"

static void	do_stuff(char *line)
{
	t_dlist		*tokens;
	t_btree		*ast;
	int			lret;

	tokens = NULL;
	if ((lret = lex_line(&tokens, line)) == LEXER_FAIL)
	{
		ft_putendl_fd("lexer error", STDERR_FILENO);
		return ;
	}
	if (!(ast = parse_tokens(NULL, tokens, lret)))
	{
		ft_putendl_fd("parser error", STDERR_FILENO);
		return ;
	}
	ft_putubt(ast, &astputelem);
	ft_btdel(&ast, &ast_btdel);
	ft_dlstdel(&tokens, &tokens_lstdel);
}

static void	read_loop(const char *pr, t_rl_opts *opts, t_dlist **hist)
{
	int			status;
	char		*line;
	int			limit;

	limit = 100;
	while ((status = ft_readline(&line, pr, opts, *hist)) != FTRL_FAIL
		&& status != FTRL_EOF)
	{
		if (status == FTRL_SIGINT)
			continue ;
		if (*line)
		{
			do_stuff(line);
			ft_putchar('\n');
			if (--limit)
				ftrl_histadd(hist, line);
			else
			{
				ft_dlstdel(hist, &ftrl_histdelf);
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
	t_dlist		*hist;

	ft_bzero(&opts, sizeof(t_rl_opts));
	opts.bell = YES;
	hist = NULL;
	read_loop(pr, &opts, &hist);
	ft_dlstdel(&hist, &ftrl_histdelf);
	return (0);
}
