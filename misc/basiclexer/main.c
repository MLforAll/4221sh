/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 19:30:28 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/28 12:00:27 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libftreadline.h"
#include "bl.h"

static void		lstdelf(void *data, size_t datsize)
{
	(void)datsize;
	free(data);
}

static void		print_tokens(char *line)
{
	t_list		*tokens;
	t_list		*tokbw;

	if (!(tokens = lex_line(line)))
	{
		ft_putendl_fd("tokens error", STDERR_FILENO);
		return ;
	}
	ft_putendl("------------------------");
	ft_putendl("|         tokens       |");
	ft_putendl("------------------------");
	tokbw = tokens;
	while (tokbw)
	{
		ft_putstr("Token: ");
		ft_putstr(((t_token*)(tokbw->content))->toks);
		ft_putstr(" | Type: ");
		ft_putnbr((int)((t_token*)(tokbw->content))->type);
		ft_putchar('\n');
		tokbw = tokbw->next;
	}
	ft_lstdel(&tokens, &lstdelf);
}

static void		read_loop(const char *pr, t_rl_opts *opts, t_rl_hist **hist)
{
	char		*line;
	int			limit;

	limit = 100;
	while ((line = ft_readline(pr, opts, *hist)))
	{
		print_tokens(line);
		if (--limit)
		{
			ft_histadd(hist, line);
			ft_putendl("------------------------");
			ft_putstr("Request to lexer: ``");
			ft_putstr(line);
			ft_putendl("'' has been added to history!");
			ft_putchar('\n');
		}
		else
		{
			ft_putstr("You've hit the limit!\n"
					"We've cleaned the history!\n");
			limit = 100;
		}
	}
}

int				main(void)
{
	const char	*pr = "\033[1;31mbasiclexer\033[0;39m$ ";
	t_rl_opts	opts;
	t_rl_hist	*hist;

	ft_bzero(&opts, sizeof(t_rl_opts));
	opts.bell = YES;
	hist = NULL;
	read_loop(pr, &opts, &hist);
	ft_putendl("Cleaning all history!");
	ft_histdel(&hist);
	return (0);
}
