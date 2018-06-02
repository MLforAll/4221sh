/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 02:21:25 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/02 05:08:33 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh_jobs.h"

void	ft_joblstdel(void *data, size_t datsize)
{
	if (datsize == 0)
		return ;
	free(((t_jobctrl*)data)->j_cmd);
	free(data);
}

void	ft_jobputstate(enum e_jobstate state)
{
	const char	*jobstates[] = {"Running", "Stopped", "Terminated", "Exited"};

	ft_putstr(jobstates[(int)state]);
}

void	ft_jobputnode(t_jobctrl *data)
{
	ft_putchar('[');
	ft_putnbr(data->j_idx);
	ft_putchar(']');
	ft_putchar((data->j_state == kJobStateRunning) ? '+' : '-');
	ft_putchar(' ');
	ft_jobputstate(data->j_state);
	ft_putchar('\t');
	ft_putendl(data->j_cmd);
}

int		ft_wait(t_list **jobnode)
{
	t_jobctrl	*jdat;
	uint8_t		ret;

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
		ft_lstdelone(jobnode, &ft_joblstdel);
	return ((int)ret);
}
