/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs_bltncmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 01:25:14 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/02 04:52:24 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "sh_jobs.h"
#include "sh.h"

int		jobs_bltn(int ac, char **av, int outfd)
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

int		fg_bltn(int ac, char **av, int outfd)
{
	t_list	*jtowake;

	(void)ac;
	(void)av;
	(void)outfd;
	jtowake = sh_job_lastest();
	/* kill(SIGCONT, pid); */
	/* wait again */
	return (EXIT_SUCCESS);
}

int		bg_bltn(int ac, char **av, int outfd)
{
	t_list	*jtowake;

	(void)ac;
	(void)av;
	(void)outfd;
	if (!(jtowake = sh_job_lastest()))
		return (EXIT_FAILURE);
	kill(((t_jobctrl*)jtowake->content)->j_pid, SIGCONT);
	return (EXIT_SUCCESS);
}
