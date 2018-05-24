/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_setenv_bltncmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:26:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/24 23:29:20 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

int		setenv_bltn(int ac, char **av, int outfd)
{
	extern char	**environ;

	if (ac > 3)
		return (sh_err(SH_ERR_TMARG, "setenv", NULL));
	if (ac == 1)
	{
		ft_puttab_fd(environ, NULL, outfd);
		return (EXIT_SUCCESS);
	}
	if (!ft_isalpha(*av[1]) || ft_strchrf(av[1], '=')
		|| (ac == 3 && ft_strchr(av[1], '=')))
		return (sh_err(SH_ERR_INVID, av[0], av[1]));
	if (ac == 3)
		set_env_var(NULL, av[1], av[2]);
	else
		set_env_from_str(NULL, av[1]);
	return (EXIT_SUCCESS);
}

int		unsetenv_bltn(int ac, char **av, int outfd)
{
	int		idx;

	(void)outfd;
	if (ac == 1)
		return (EXIT_FAILURE);
	if (!ft_isalpha(*av[1]) || ft_strchrf(av[1], '=')
		|| (ac == 3 && ft_strchr(av[1], '=')))
		return (sh_err(SH_ERR_INVID, av[0], av[1]));
	idx = 0;
	while (idx < ac)
		del_env_var(NULL, av[idx++]);
	return (EXIT_SUCCESS);
}
