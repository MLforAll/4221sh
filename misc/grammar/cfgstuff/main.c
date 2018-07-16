/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 19:55:35 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/01 20:16:26 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "bp.h"

static void	readloop(int fd)
{
	char		*cfg;
	char		*line;
	const char	*pr = "\033[0;36mbasicparser\033[0;39m$ ";
	t_rl_opts	opts;

	ft_bzero(&opts, sizeof(t_rl_opts));
	opts.bell = YES;
	if (!(cfg = ft_readfd(fd, 32)))
		return ;
	while ((line = ft_readline(pr, &opts, NULL)))
	{
		parsestuff(cfg, line);
		free(line);
	}
	free(cfg);
}

int			main(int ac, char **av)
{
	int		fd;

	if (ac < 2)
		return (1);
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (1);
	readloop(fd);
	close(fd);
	return (0);
}
