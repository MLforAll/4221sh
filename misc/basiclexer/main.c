/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 19:30:28 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/27 20:08:21 by kdumarai         ###   ########.fr       */
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

	if (!(tokens = lex_line(line)))
	{
		ft_putendl_fd("tokens error", STDERR_FILENO);
		return ;
	}
	ft_putendl("------------------------");
	ft_putendl("|         tokens       |");
	ft_putendl("------------------------");
	ft_putlst(tokens);
	ft_lstdel(&tokens, &lstdelf);
	ft_putchar('\n');
}

int			main(void)
{
	const char	*pr = "\033[1;31mbasiclexer\033[0;39m$ ";
	t_rl_opts	opts;
	char		*line;

	ft_bzero(&opts, sizeof(t_rl_opts));
	opts.bell = YES;
	while ((line = ft_readline(pr, &opts, NULL)))
		print_tokens(line);
	return (0);
}
