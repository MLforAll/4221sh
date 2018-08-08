/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmdexec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 20:09:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/08 18:55:24 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "sh_jobs.h"
#include "sh.h"

static int		cmd_chk(char *path)
{
	t_errs	code;
	t_errs	noent;
	char	*pathenv;

	if (!path)
		return ((int)SH_ERR_UNDEFINED);
	noent = SH_ERR_NOENT;
	if (!ft_strchr(path, '/'))
	{
		if ((pathenv = get_env_var(NULL, "PATH")) && *pathenv)
			return ((int)SH_ERR_NOCMD);
		noent = SH_ERR_NOCMD;
	}
	if ((code = get_errcode_for_path(path, X_OK, NO, NO)) == SH_ERR_UNDEFINED)
		return (-1);
	if (code == SH_ERR_NOENT)
		return ((int)noent);
	return ((int)code);
}

static void		restore_bakfds(t_tab *bakfds)
{
	unsigned long	idx;
	t_bakfds		*curr;

	if (!bakfds)
		return ;
	if (bakfds->oc_size > 0)
	{
		idx = bakfds->count;
		while (idx--)
		{
			curr = (t_bakfds*)bakfds->data + idx;
			(void)close(curr->orig);
			(void)dup2(curr->bak, curr->orig);
			(void)close(curr->bak);
		}
	}
	ft_ttabdel(bakfds, NULL);
}

static int		exec_core(t_cmdnode *cmddat, t_uint8 forkdes, char **env)
{
	int		tmp;
	t_tab	bakfds;
	t_tab	*bakfds_ptr;

	if (!forkdes && !ft_ttabnew(&bakfds, sizeof(t_bakfds)))
		return (sh_err_ret(SH_ERR_MALLOC, NULL, NULL, EXIT_FAILURE));
	bakfds_ptr = (forkdes) ? NULL : &bakfds;
	exec_pipe(cmddat);
	if ((tmp = exec_redir(cmddat, bakfds_ptr)) || cmddat->builtin)
	{
		if (tmp == EXIT_SUCCESS)
			tmp = (cmddat->builtin)((int)ft_tablen(cmddat->c_av), cmddat->c_av);
		restore_bakfds(bakfds_ptr);
		return (tmp);
	}
	if (!cmddat->c_path)
		return (EXIT_SUCCESS);
	(void)chg_env_var(env, "_", cmddat->c_path);
	(void)execve(cmddat->c_path, cmddat->c_av, env);
	if ((tmp = cmd_chk(cmddat->c_path)) >= 0)
		return (sh_err_ret((t_errs)tmp, NULL, cmddat->c_path, 127));
	shell_init(cmddat->c_av);
	return ((exec_shell(cmddat->c_path) == EXIT_SUCCESS) ? EXIT_SUCCESS : 127);
}

static int		exec_setup(t_cmdnode *cmddat,
							t_uint8 async,
							pid_t *spid,
							char **env)
{
	t_uint8		forkdes;
	pid_t		pid;
	t_list		**jobnode;
	char		**env_bak;
	extern char	**environ;

	if (!(forkdes = (async || !cmddat->builtin
		|| cmddat->stdin_fd != -1 || cmddat->stdout_fd != -1)))
		return (exec_core(cmddat, forkdes, env));
	env_bak = environ;
	environ = NULL;
	pid = fork();
	environ = env_bak;
	if (pid == -1)
		return (sh_err_ret(SH_ERR_FORK, "fork()", NULL, -1));
	if (pid == 0)
	{
		switch_traps(FALSE);
		exit(exec_core(cmddat, forkdes, env));
	}
	(spid) ? *spid = pid : (void)0;
	jobnode = (spid) ? NULL : sh_job_add(cmddat->c_path, pid,
										kJobStateRunning, !async);
	return ((async) ? -1 : ft_wait(jobnode));
}

int				exec_cmd(t_cmdnode *cmddat, \
						t_uint8 async, \
						pid_t *spid, \
						char **env)
{
	extern char	**g_lvars;
	extern char	**environ;
	char		**tmp;
	t_uint8		is_cmd;

	if (!cmddat)
		return (EXIT_FAILURE);
	is_cmd = (cmddat->builtin || cmddat->c_path);
	if (cmddat->c_vars && !cmddat->builtin)
	{
		tmp = cmddat->c_vars;
		while (*tmp)
			set_env_from_str((is_cmd) ? NULL : &g_lvars, *(tmp++));
	}
	return (exec_setup(cmddat, async, spid, (env) ? env : environ));
}
