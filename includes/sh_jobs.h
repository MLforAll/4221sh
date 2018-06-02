/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 04:46:03 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/02 05:08:40 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_JOBS_H
# define SH_JOBS_H

# include "libft.h"

/*
** job control struct
*/

enum			e_jobstate
{
	kJobStateRunning,
	kJobStateStopped,
	kJobStateTerminated,
	kJobStateExited
};

typedef struct	s_jobctrl
{
	int				j_idx;
	enum e_jobstate	j_state;
	char			*j_cmd;
	pid_t			j_pid;
	uint8_t			j_exval;
}				t_jobctrl;

/*
** item creation - print - deletion
** global g_jobslst mgmt
*/

uint8_t			sh_job_put(int n);
t_list			*sh_job_lastest(void);
t_list			**sh_job_add(char *cmd, pid_t pid);

/*
** signal hdl
*/

void			sh_jb_sighdl(int sigc);

/*
** wait for a job to be updated by signal hdl
*/

int				ft_wait(t_list **jobnode);

/*
** utilities
*/

void			ft_joblstdel(void *data, size_t datsize);
void			ft_jobputnode(t_jobctrl *data);
void			ft_jobputstate(enum e_jobstate state);

#endif
