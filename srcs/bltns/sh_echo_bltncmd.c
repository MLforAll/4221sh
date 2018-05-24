/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_echo_bltncmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:26:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/24 23:30:06 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

int		echo_bltn(int ac, char **av, int outfd)
{
	int		nonl;

	nonl = 0;
	if (ac > 1 && ft_strcmp(av[1], "-n") == 0)
	{
		nonl = 1;
		av++;
	}
	while (*(++av))
	{
		ft_putstr_fd(*av, outfd);
		if (*(av + 1))
			ft_putchar_fd(' ', outfd);
	}
	if (!nonl)
		ft_putchar_fd('\n', outfd);
	return (EXIT_SUCCESS);
}
