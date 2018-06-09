/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs_sigchld.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 04:41:14 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/09 04:03:33 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "sh_jobs.h"
#include "sh.h"

extern t_list	*g_jobslst;

static void		insert_job_msg(t_jobctrl *jdat)
{
	t_str	rl_rld_str;
	char	*nbr_s;

	rl_rld_str = ft_tstrnew();
	if (!rl_rld_str.s)
		return ;
	if (!(nbr_s = ft_itoa(jdat->j_idx)))
	{
		ft_tstrdel(&rl_rld_str);
		return ;	
	}
	ft_tstrcpy(&rl_rld_str, "[");
	ft_tstrcat(&rl_rld_str, nbr_s);
	free(nbr_s);
	ft_tstrcat(&rl_rld_str, "]\t");
	ft_tstrcat(&rl_rld_str, jdat->j_cmd);
	ft_tstrcat(&rl_rld_str, "\t=>\t");
	ft_tstrcat(&rl_rld_str, (char*)ft_jobputstate(jdat->j_state, NO));
	if (!ftrl_insert_msg(rl_rld_str.s, STDOUT_FILENO, YES))
	{
		ft_putendl(rl_rld_str.s);
		ft_tstrdel(&rl_rld_str);
	}
}

static void		act_upon(t_jobctrl *jdat, int exval)
{
	if (WIFEXITED(exval))
	{
		jdat->j_state = kJobStateExited;
		jdat->j_exval = WEXITSTATUS(exval);
		return ;
	}
	if (jdat->j_state == kJobStateTerminated)
		return ;
	if (WIFSTOPPED(exval))
	{
		jdat->j_state = kJobStateStopped;
		insert_job_msg(jdat);
	}
	if (WIFSIGNALED(exval))
	{
		jdat->j_state = kJobStateTerminated;
		//sh_child_signaled(WTERMSIG(exval));
		insert_job_msg(jdat);
	}
}

void			sh_jb_sighdl(int sigc)
{
	t_list		*tmp;
	t_jobctrl	*jdat;
	int			exval;

	if (sigc != SIGCHLD || !(tmp = g_jobslst))
		return ;
	signal(SIGCHLD, SIG_DFL);
	while (tmp)
	{
		jdat = (t_jobctrl*)tmp->content;
		exval = 0;
		if (waitpid(jdat->j_pid, &exval, WNOHANG | WUNTRACED) > 0)
			act_upon(jdat, exval);
		tmp = tmp->next;
	}
	signal(SIGCHLD, &sh_jb_sighdl);
}
