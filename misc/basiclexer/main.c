/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 19:30:28 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/05 18:17:06 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftreadline.h"
#include "bl.h"
#include "blintern.h"

static void		add_to_hist(int *limit, char *line, t_rl_hist **hist)
{
	if (--*limit)
	{
		ft_histadd(hist, line);
		ft_putstr("Request to lexer: ``");
		ft_putstr(line);
		ft_putendl("'' has been added to history!");
	}
	else
	{
		ft_histdel(hist);
		*limit = 100;
		ft_putstr("You've hit the limit!\n"
				"We've cleaned the history!\n");
	}
	ft_putchar('\n');
}

static void		read_loop(const char *pr, t_rl_opts *opts, t_rl_hist **hist)
{
	char		*line;
	int			limit;

	limit = 100;
	while ((line = ft_readline(pr, opts, *hist)))
	{
		if (*line)
		{
			print_tokens(line);
			add_to_hist(&limit, line, hist);
		}
		free(line);
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
	ft_histdel(&hist);
	return (0);
}
