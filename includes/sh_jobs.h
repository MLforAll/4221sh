/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 04:46:03 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/06 19:32:13 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_JOBS_H
# define SH_JOBS_H

# include "libft.h"

/*
** job control struct
*/

typedef enum	e_jobstate
{
	kJobStateRunning,
	kJobStateStopped,
	kJobStateTerminated,
	kJobStateExited
}				t_jobstate;

typedef struct	s_jobctrl
{
	int				j_idx;
	enum e_jobstate	j_state;
	char			*j_cmd;
	pid_t			j_pid;
	t_uint8			j_exval;
	t_uint8			j_foreground;
	char			reserved_pad[2];
}				t_jobctrl;

/*
** item creation - print - deletion
** global g_jobslst mgmt
*/

t_uint8			sh_job_put(int n);
t_list			**sh_job_idx(int idx);
t_list			**sh_job_lastest(void);

t_list			**sh_job_add(char *cmd, \
							pid_t pid, \
							t_jobstate state, \
							t_uint8 foreground);

void			sh_jobs_rmall(void);

/*
** signal hdl
*/

void			sh_jb_sighdl(int sigc);

/*
** wait for a job to be updated by signal hdl
*/

int				ft_wait(t_list **jobnode);

/*
** async
*/

void			sh_jobop_lock(void);
void			sh_jobop_unlock(void);
void			sh_jobop_reinit(void);

/*
** utilities
*/

void			ft_joblstdel(void *data, size_t datsize);
void			ft_jobputnode(t_jobctrl *data);
const char		*ft_jobputstate(enum e_jobstate state, t_uint8 print);
void			sh_jb_act_upon(t_jobctrl *jdat, int exval);

#endif
