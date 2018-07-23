/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_job_put.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 05:32:23 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/23 23:16:31 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh_jobs.h"

extern t_list	*g_jobslst;

static t_uint8	sh_job_put_action(int n, t_list ***tmp, t_uint8 *ret)
{
	t_list		**bak;
	t_jobctrl	*dat;

	dat = (t_jobctrl*)(**tmp)->content;
	if (n < 1 || n == dat->j_idx)
	{
		*ret = TRUE;
		ft_jobputnode(dat);
		if (dat->j_state == kJobStateTerminated
			|| dat->j_state == kJobStateExited)
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
