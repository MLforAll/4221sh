/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 02:55:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/06 19:38:22 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh_jobs.h"

extern t_list	*g_jobslst;
t_list			*g_jobslst = NULL;

t_list			**sh_job_idx(int idx)
{
	t_list	**tmp;

	if (!(tmp = &g_jobslst))
		return (NULL);
	sh_jobop_lock();
	while ((*tmp) && idx--)
		tmp = &(*tmp)->next;
	sh_jobop_unlock();
	return ((idx > 0) ? NULL : tmp);
}

t_list			**sh_job_lastest(void)
{
	t_list	**tmp;

	tmp = &g_jobslst;
	if (!*tmp)
		return (NULL);
	sh_jobop_lock();
	while ((*tmp)->next)
		tmp = &(*tmp)->next;
	sh_jobop_unlock();
	return (tmp);
}

t_list			**sh_job_add(char *cmd,\
							pid_t pid, \
							t_jobstate state, \
							t_uint8 foreground)
{
	t_jobctrl	*jdat;
	t_list		*node;
	t_list		**tmp;

	sh_jobop_lock();
	tmp = &g_jobslst;
	while (*tmp && (*tmp)->next)
		tmp = &(*tmp)->next;
	if (!(jdat = ft_memalloc(sizeof(t_jobctrl))))
		return (NULL);
	jdat->j_idx = (!*tmp) ? 1 : ((t_jobctrl*)(*tmp)->content)->j_idx;
	jdat->j_state = state;
	jdat->j_cmd = ft_strdup((cmd) ? cmd : "builtin");
	jdat->j_pid = pid;
	jdat->j_foreground = foreground;
	if (!(node = ft_lstnew_nomalloc(jdat, sizeof(t_jobctrl))))
	{
		free(jdat->j_cmd);
		free(jdat);
		return (NULL);
	}
	tmp = (*tmp) ? &(*tmp)->next : tmp;
	*tmp = node;
	sh_jobop_unlock();
	return (tmp);
}

void			sh_jobs_rmall(void)
{
	if (!g_jobslst)
		return ;
	ft_lstdel(&g_jobslst, &ft_joblstdel);
	ft_putlst(g_jobslst);
	sh_jobop_unlock();
}
