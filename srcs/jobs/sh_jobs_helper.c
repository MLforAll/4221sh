/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 02:21:25 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/30 02:39:09 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh_jobs.h"

void			ft_joblstdel(void *data, size_t datsize)
{
	if (datsize == 0)
		return ;
	free(((t_jobctrl*)data)->j_cmd);
	free(data);
}

const char		*ft_jobputstate(enum e_jobstate state, t_uint8 print)
{
	const char	*jobstates[] = {"Running", "Stopped", "Terminated", "Exited"};

	if (print)
		ft_putstr(jobstates[(int)state]);
	return (jobstates[(int)state]);
}

void			ft_jobputnode(t_jobctrl *data)
{
	ft_putchar('[');
	ft_putnbr(data->j_idx);
	ft_putchar(']');
	ft_putchar((data->j_state == kJobStateRunning) ? '+' : '-');
	ft_putchar(' ');
	ft_jobputstate(data->j_state, YES);
	ft_putchar('\t');
	ft_putendl(data->j_cmd);
}

int				ft_wait(t_list **jobnode)
{
	t_jobctrl	*jdat;
	int			exval;

	jdat = (t_jobctrl*)(*jobnode)->content;
	if (waitpid(jdat->j_pid, &exval, WUNTRACED) <= 0)
	{
		g_curr_process = 0;
		return (EXIT_FAILURE);
	}
	sh_jb_act_upon(jdat, exval);
	if (!WIFSTOPPED(exval))
	{
		sh_jobop_lock();
		ft_lstdelone(jobnode, &ft_joblstdel);
		sh_jobop_unlock();
	}
	g_curr_process = 0;
	return (WEXITSTATUS(exval));
}
