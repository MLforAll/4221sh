/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_echo_bltncmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:26:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/26 19:01:38 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

int		echo_bltn(int ac, char **av)
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
		ft_putstr_fd(*av, STDOUT_FILENO);
		if (*(av + 1))
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!nonl)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
