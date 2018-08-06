/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_source_bltncmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:26:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/06 05:10:39 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

int		source_bltn(int ac, char **av)
{
	if (ac == 1)
	{
		sh_err(SH_ERR_ARGREQ, *av, NULL);
		ft_putendl_fd("source: usage: source filename",
						STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (exec_shell(av[1]));
}
