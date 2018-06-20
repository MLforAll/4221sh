/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 02:55:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/20 04:18:17 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh_jobs.h"

t_list		*g_jobslst = NULL;
uint8_t		g_jobop = NO;

uint8_t		sh_job_put(int n)
{
	t_list		**tmp;
	t_list		**bak;
	t_jobctrl	*dat;
	uint8_t		ret;

	sh_jobop_getlock();
	g_jobop = YES;
	tmp = &g_jobslst;
	ret = FALSE;
	while (*tmp)
	{
		dat = (t_jobctrl*)(*tmp)->content;
		if (n < 1 || n == dat->j_idx)
		{
			ret = TRUE;
			ft_jobputnode(dat);
			if (dat->j_state == kJobStateTerminated)
			{
				bak = tmp;
				tmp = &(*tmp)->next;
				ft_lstdelone(bak, &ft_joblstdel);
				continue ;
			}
		}
		tmp = &(*tmp)->next;
	}
	g_jobop = NO;
	return (ret);
}

t_list		**sh_job_idx(int idx)
{
	t_list	**tmp;

	if (!(tmp = &g_jobslst))
		return (NULL);
	sh_jobop_getlock();
	g_jobop = YES;
	while ((*tmp) && idx--)
		tmp = &(*tmp)->next;
	g_jobop = NO;
	return ((idx > 0) ? NULL : tmp);
}

t_list		**sh_job_lastest(void)
{
	t_list	**tmp;

	tmp = &g_jobslst;
	if (!*tmp)
		return (NULL);
	sh_jobop_getlock();
	g_jobop = YES;
	while ((*tmp)->next)
		tmp = &(*tmp)->next;
	g_jobop = NO;
	return (tmp);
}

t_list		**sh_job_add(char *cmd, pid_t pid)
{
	t_jobctrl	*jdat;
	t_list		*node;
	t_list		**tmp;

	sh_jobop_getlock();
	g_jobop = YES;
	tmp = &g_jobslst;
	while (*tmp && (*tmp)->next)
		tmp = &(*tmp)->next;
	if (!(jdat = ft_memalloc(sizeof(t_jobctrl))))
		return (NULL);
	jdat->j_idx = (!*tmp) ? 1 : ((t_jobctrl*)(*tmp)->content)->j_idx;
	jdat->j_state = kJobStateRunning;
	jdat->j_cmd = ft_strdup(cmd);
	jdat->j_pid = pid;
	if (!(node = ft_lstnew_nomalloc(jdat, sizeof(t_jobctrl))))
	{
		free(jdat->j_cmd);
		free(jdat);
		return (NULL);
	}
	tmp = (*tmp) ? &(*tmp)->next : tmp;
	*tmp = node;
	g_jobop = NO;
	return (tmp);
}
