/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_setenv_bltncmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:26:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/26 19:06:24 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

static t_uint8	is_id_valid(int ac, char **av)
{
	if (!ft_isalpha(*av[1]) || ft_strchrf(av[1], '=')
		|| (ac == 3 && ft_strchr(av[1], '=')))
		return (FALSE);
	return (TRUE);
}

int				setenv_bltn(int ac, char **av)
{
	extern char	**environ;

	if (ac > 3)
		return (sh_err(SH_ERR_TMARG, av[0], NULL));
	if (ac == 1)
	{
		ft_puttab(environ, NULL);
		return (EXIT_SUCCESS);
	}
	if (!is_id_valid(ac, av))
		return (sh_err(SH_ERR_INVID, av[0], av[1]));
	if (ac == 3)
		set_env_var(NULL, av[1], av[2]);
	else
		set_env_from_str(NULL, av[1]);
	return (EXIT_SUCCESS);
}

int				unsetenv_bltn(int ac, char **av)
{
	int		idx;

	if (ac == 1)
		return (EXIT_FAILURE);
	if (!is_id_valid(ac, av))
		return (sh_err(SH_ERR_INVID, av[0], av[1]));
	idx = 0;
	while (++idx < ac)
	{
		if (getenv(av[idx]))
			del_env_var(NULL, av[idx]);
		else
			del_lvar(av[idx]);
	}
	return (EXIT_SUCCESS);
}
