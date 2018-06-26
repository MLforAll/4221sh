/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exit_bltncmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:26:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/26 19:00:00 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

int		exit_bltn(int ac, char **av)
{
	char	*last_cmd_ret;

	if (ac > 2)
		return (sh_err(SH_ERR_TMARG, av[0], NULL));
	if (ac == 1)
	{
		last_cmd_ret = getenv("?");
		exit((last_cmd_ret) ? ft_atoi(last_cmd_ret) : EXIT_SUCCESS);
	}
	if (!ft_strisnumeric(av[1]))
		exit(sh_err_ret(SH_ERR_NUMARG, av[0], av[1], 255));
	exit(ft_atoi(av[1]));
	return (EXIT_SUCCESS);
}
