/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 02:55:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/31 04:25:26 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

t_list		*g_jobslst = NULL;

uint8_t		sh_job_put(int n)
{
	t_list		*tmp;
	t_jobctrl	*dat;

	tmp = g_jobslst;
	while (tmp)
	{
		dat = (t_jobctrl*)tmp->content;
		if (n < 1 || n == dat->j_idx)
		{
			ft_putchar('[');
			ft_putnbr(dat->j_idx);
			ft_putchar(']');
			ft_putchar((dat->j_state == kJobStateRunning) ? '+' : '-');
			ft_putchar(' ');
			ft_putstr((dat->j_state == kJobStateRunning) ? "Running" : "Other");
			ft_putchar('\t');
			ft_putendl(dat->j_cmd);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

t_list		*sh_job_lastest(void)
{
	t_list	*tmp;

	tmp = g_jobslst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

uint8_t		sh_job_add(char *cmd, pid_t pid)
{
	t_jobctrl	*j_data;
	t_list		*node;
	t_list		**tmp;

	tmp = &g_jobslst;
	while (*tmp && (*tmp)->next)
		tmp = &(*tmp)->next;
	if (!(j_data = ft_memalloc(sizeof(t_jobctrl))))
		return (FALSE);
	j_data->j_idx = (!*tmp) ? 1 : ((t_jobctrl*)(*tmp)->content)->j_idx;
	j_data->j_state = kJobStateRunning;
	j_data->j_cmd = ft_strdup(cmd);
	j_data->j_pid = pid;
	if (!(node = ft_lstnew(NULL, 0)))
	{
		free(j_data->j_cmd);
		free(j_data);
		return (FALSE);
	}
	node->content = j_data;
	node->content_size = sizeof(t_jobctrl);
	tmp = (*tmp) ? &(*tmp)->next : tmp;
	*tmp = node;
	return (TRUE);
}
