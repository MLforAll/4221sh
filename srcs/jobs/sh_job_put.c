/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_job_put.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 05:32:23 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/09 15:15:35 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh_jobs.h"

extern t_list	*g_jobslst;

t_uint8			sh_job_put(int n)
{
	t_list		**tmp;
	t_jobctrl	*dat;
	t_uint8		ret;

	sh_jobop_lock();
	tmp = &g_jobslst;
	ret = FALSE;
	while (*tmp)
	{
		dat = (t_jobctrl*)(*tmp)->content;
		if (n < 1 || n == dat->j_idx)
		{
			ret = TRUE;
			ft_jobputnode(dat);
			if (dat->j_state == kJobStateTerminated
				|| dat->j_state == kJobStateExited)
			{
				ft_lstdelone(tmp, &ft_joblstdel);
				continue ;
			}
		}
		tmp = &(*tmp)->next;
	}
	sh_jobop_unlock();
	return (ret);
}
