/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs_bltncmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 01:25:14 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/14 10:12:50 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "sh_jobs.h"
#include "sh.h"

int				jobs_bltn(int ac, char **av, int outfd)
{
	int		jn;

	(void)outfd;
	if (ac == 1)
	{
		sh_job_put(0);
		return (EXIT_SUCCESS);
	}
	if (ft_secatoi(&jn, av[1]) == 0)
	{
		ft_putendl_fd("ft_secatoi(): n is out of range!", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!sh_job_put(jn))
	{
		sh_err(SH_ERR_NOJOB, av[0], av[1]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static t_list	**kick_job_back(int ac, char **av)
{
	t_list	**jtowake;
	int		idx;

	if (ac == 1)
		idx = -1;
	else if (ft_secatoi(&idx, av[1]) == 0)
	{
		ft_putendl_fd("ft_secatoi(): n is out of range!", STDERR_FILENO);
		return (NULL);
	}
	if (!(jtowake = (idx == -1) ? sh_job_lastest() : sh_job_idx(idx)))
	{
		ft_putendl_fd("kick_job_back(): such job does not exist!", STDERR_FILENO);
		return (NULL);
	}
	kill(((t_jobctrl*)(*jtowake)->content)->j_pid, SIGCONT);
	((t_jobctrl*)(*jtowake)->content)->j_state = kJobStateRunning;
	return (jtowake);
}

int				fg_bltn(int ac, char **av, int outfd)
{
	t_list	**jtowake;

	(void)outfd;
	if (!(jtowake = kick_job_back(ac, av)))
		return (EXIT_FAILURE);
	return (ft_wait(jtowake));
}

int				bg_bltn(int ac, char **av, int outfd)
{
	t_list	**jtowake;

	(void)outfd;
	if (!(jtowake = kick_job_back(ac, av)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
