/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs_sigchld.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 04:41:14 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/02 05:09:34 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "sh_jobs.h"
#include "sh.h"

extern t_list	*g_jobslst;

static void		act_upon(t_jobctrl *jdat, int exval)
{
	if (jdat->j_state != kJobStateTerminated && WIFSTOPPED(exval))
	{
		jdat->j_state = kJobStateStopped;
		ft_putchar('[');
		ft_putnbr(jdat->j_idx);
		ft_putchar(']');
		ft_putchar('\t');
		ft_putstr(jdat->j_cmd);
		ft_putstr("\t=>\t");
		ft_jobputstate(jdat->j_state);
		ft_putchar('\n');
	}
	if (jdat->j_state != kJobStateTerminated && WIFSIGNALED(exval))
	{
		sh_child_signaled(WTERMSIG(exval));
		jdat->j_state = kJobStateTerminated;
	}
	if (WIFEXITED(exval))
	{
		jdat->j_state = kJobStateExited;
		jdat->j_exval = WEXITSTATUS(exval);
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
