/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 02:21:25 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/09 15:10:11 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh_jobs.h"

void				ft_joblstdel(void *data, size_t datsize)
{
	if (datsize == 0)
		return ;
	free(((t_jobctrl*)data)->j_cmd);
	free(data);
}

inline const char	*ft_jobputstate(enum e_jobstate state)
{
	const char	*jobstates[] = {"Running", "Stopped", "Terminated", "Exited"};

	return (jobstates[(int)state]);
}

void				ft_jobputnode(t_jobctrl *data)
{
	ft_putchar('[');
	ft_putnbr(data->j_idx);
	ft_putchar(']');
	ft_putchar((data->j_state == kJobStateRunning) ? '+' : '-');
	ft_putchar(' ');
	ft_putstr(ft_jobputstate(data->j_state));
	ft_putchar('\t');
	ft_putendl(data->j_cmd);
}

int					ft_wait(t_list **jobnode)
{
	t_jobctrl	*jdat;
	int			exval;

	jdat = (t_jobctrl*)(*jobnode)->content;
	if (waitpid(jdat->j_pid, &exval, WUNTRACED) <= 0)
	{
		jdat->j_foreground = FALSE;
		return (EXIT_FAILURE);
	}
	sh_jb_act_upon(jdat, exval);
	if (!WIFSTOPPED(exval))
	{
		sh_jobop_lock();
		ft_lstdelone(jobnode, &ft_joblstdel);
		sh_jobop_unlock();
	}
	else
		jdat->j_foreground = FALSE;
	return (WEXITSTATUS(exval));
}
