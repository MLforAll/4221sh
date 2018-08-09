/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs_sigchld.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 04:41:14 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/09 05:40:47 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "sh_jobs.h"
#include "sh.h"

extern t_list		*g_jobslst;

static void			insert_job_msg(t_jobctrl *jdat, const char *state_str)
{
	t_str	rl_rld_str;
	char	*nbr_s;

	if (!ft_tstrnew(&rl_rld_str))
		return ;
	if (!(nbr_s = ft_itoa(jdat->j_idx)))
	{
		ft_tstrdel(&rl_rld_str);
		return ;
	}
	(void)ft_tstrcpy(&rl_rld_str, "[");
	(void)ft_tstrcat(&rl_rld_str, nbr_s);
	free(nbr_s);
	(void)ft_tstrcat(&rl_rld_str, "]\t");
	(void)ft_tstrcat(&rl_rld_str, jdat->j_cmd);
	(void)ft_tstrcat(&rl_rld_str, "\t=>\t");
	(void)ft_tstrcat(&rl_rld_str, state_str);
	if (!ftrl_insert_msg(rl_rld_str.s, STDOUT_FILENO, YES))
	{
		ft_putendl(rl_rld_str.s);
		ft_tstrdel(&rl_rld_str);
	}
}

static const char	*get_sig_str(int sigc)
{
	const char	*errs[30] = {"Hangup", NULL, NULL, "Illegal instruction",
		"Trace/BPT trap", "Abort trap", "EMT trap", "Floating point exception",
		"Killed", "Bus error", "Segmentation fault",
		"Bad system call", NULL, "Alarm clock", "Terminated",
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, "Cputime limit exceeded",
		"Filesize limit exceeded", "Virtual timer expired",
		"Profiling timer expired", NULL, NULL,
		"User defined signal 1", "User defined signal 2"};

	if (sigc <= 0 || sigc > 31)
		return (NULL);
	return (errs[sigc - 1]);
}

void				sh_jb_act_upon(t_jobctrl *jdat, int exval)
{
	const char	*tmp;

	if (WIFEXITED(exval))
	{
		jdat->j_state = kJobStateExited;
		jdat->j_exval = WEXITSTATUS(exval);
		if (!jdat->j_foreground)
			insert_job_msg(jdat, ft_jobputstate(jdat->j_state));
		return ;
	}
	if (jdat->j_state == kJobStateTerminated)
		return ;
	if (WIFSTOPPED(exval))
	{
		jdat->j_state = kJobStateStopped;
		insert_job_msg(jdat, ft_jobputstate(jdat->j_state));
	}
	if (WIFSIGNALED(exval))
	{
		jdat->j_state = kJobStateTerminated;
		if ((tmp = get_sig_str(WTERMSIG(exval))))
			insert_job_msg(jdat, tmp);
	}
}

void				sh_jb_sighdl(int sigc)
{
	t_list		*tmp;
	t_jobctrl	*jdat;
	int			exval;

	if (sigc != SIGCHLD || !(tmp = g_jobslst))
		return ;
	(void)signal(SIGCHLD, SIG_DFL);
	sh_jobop_lock();
	while (tmp)
	{
		jdat = (t_jobctrl*)tmp->content;
		exval = 0;
		if (!jdat->j_foreground
			&& waitpid(jdat->j_pid, &exval, WNOHANG | WUNTRACED) > 0)
			sh_jb_act_upon(jdat, exval);
		tmp = tmp->next;
	}
	sh_jobop_unlock();
	(void)signal(SIGCHLD, &sh_jb_sighdl);
}
