/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 02:21:25 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/03 05:33:09 by kdumarai         ###   ########.fr       */
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
	t_uint8		ret;

	if (!jobnode)
		return (-1);
	while (*jobnode)
	{
		jdat = (t_jobctrl*)(*jobnode)->content;
		if (jdat->j_state != kJobStateRunning)
			break ;
	}
	if (!*jobnode)
		return (-1);
	ret = jdat->j_exval;
	if (jdat->j_state == kJobStateExited)
	{
		sh_jobop_lock();
		ft_lstdelone(jobnode, &ft_joblstdel);
		sh_jobop_unlock();
	}
	return ((int)ret);
}

/*
**	waitpid(pid, &exval, WUNTRACED);
**	if (WIFSTOPPED(exval))
**		sh_job_add(cmddat->c_path, pid);
**	if (WIFSIGNALED(exval))
**		sh_child_signaled(WTERMSIG(exval));
**	return (WEXITSTATUS(exval));
*/
