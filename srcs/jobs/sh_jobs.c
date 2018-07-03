/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 02:55:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/03 05:02:34 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh_jobs.h"

t_list		*g_jobslst = NULL;

static t_uint8	sh_job_put_action(int n, t_list ***tmp, t_uint8 *ret)
{
	t_list		**bak;
	t_jobctrl	*dat;

	dat = (t_jobctrl*)(**tmp)->content;
	if (n < 1 || n == dat->j_idx)
	{
		*ret = TRUE;
		ft_jobputnode(dat);
		if (dat->j_state == kJobStateTerminated)
		{
			bak = *tmp;
			*tmp = &(**tmp)->next;
			ft_lstdelone(bak, &ft_joblstdel);
			return (TRUE);
		}
	}
	return (FALSE);
}

t_uint8			sh_job_put(int n)
{
	t_list		**tmp;
	t_uint8		ret;

	sh_jobop_lock();
	tmp = &g_jobslst;
	ret = FALSE;
	while (*tmp)
	{
		if (sh_job_put_action(n, &tmp, &ret))
			continue ;
		tmp = &(*tmp)->next;
	}
	sh_jobop_unlock();
	return (ret);
}

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

t_list			**sh_job_add(char *cmd, pid_t pid, enum e_jobstate state)
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
	extern t_uint8	g_jobop;

	ft_lstdel(&g_jobslst, &ft_joblstdel);
	ft_putlst(g_jobslst);
	g_jobop = NO;
}
