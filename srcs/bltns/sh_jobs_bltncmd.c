/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs_bltncmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 01:25:14 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/28 01:39:10 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

int		jobs_bltn(int ac, char **av, int outfd)
{
	(void)ac;
	(void)av;
	ft_putendl_fd("Not currently available!", outfd);
	return (EXIT_SUCCESS);
}
