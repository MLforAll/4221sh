/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmdexec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 20:09:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/28 03:41:54 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "sh_jobs.h"
#include "sh.h"

static int	cmd_chk(char *path)
{
	int		code;
	int		noent;
	char	*pathenv;

	if (!path)
		return (SH_ERR_UNDEFINED);
	noent = SH_ERR_NOENT;
	if (!ft_strchr(path, '/'))
	{
		if ((pathenv = getenv("PATH")) && *pathenv)
			return (SH_ERR_NOCMD);
		noent = SH_ERR_NOCMD;
	}
	if ((code = get_errcode_for_path(path, X_OK, NO)) == SH_ERR_UNDEFINED)
		return (-1);
	if (code == SH_ERR_NOENT)
		return (noent);
	return (code);
}

static void	restore_bakfds(t_tab *bakfds)
{
	unsigned long	idx;
	t_bakfds		*curr;

	if (!bakfds)
		return ;
	if (bakfds->oc_size > 0)
	{
		idx = bakfds->oc_size - bakfds->data_size;
		while (TRUE)
		{
			curr = (t_bakfds*)(bakfds->data + idx);
			close(curr->orig);
			dup2(curr->bak, curr->orig);
			close(curr->bak);
			if (idx == 0)
				break ;
			idx -= bakfds->data_size;
		}
	}
	ft_ttabdel(bakfds);
}

static int	exec_core(t_cmdnode *cmddat, uint8_t forkdes, char **env)
{
	int		tmp;
	t_tab	bakfds;
	t_tab	*bakfds_ptr;

	if (!forkdes)
		bakfds = ft_ttabnew(sizeof(t_bakfds));
	bakfds_ptr = (forkdes) ? NULL : &bakfds;
	exec_pipe(cmddat);
	exec_redir(cmddat, bakfds_ptr);
	if (cmddat->builtin)
	{
		tmp = (cmddat->builtin)((int)ft_tablen(cmddat->c_av), cmddat->c_av);
		restore_bakfds(bakfds_ptr);
		return (tmp);
	}
	chg_env_var(env, "_", cmddat->c_path);
	execve(cmddat->c_path, cmddat->c_av, env);
	if ((tmp = cmd_chk(cmddat->c_path)) >= 0)
		return (sh_err_ret(tmp, NULL, cmddat->c_path, 127));
	tmp = (exec_shell(cmddat->c_path) == EXIT_SUCCESS) ? EXIT_SUCCESS : 127;
	restore_bakfds(bakfds_ptr);
	return (tmp);
}

static int	exec_bincmd(t_cmdnode *cmddat, int async, pid_t *spid, char **env)
{
	uint8_t	forkdes;
	pid_t	pid;
	t_list	**jobnode;

	if (!(forkdes = (async || cmddat->c_path
		|| cmddat->stdin_fd != -1 || cmddat->stdout_fd != -1)))
		return (exec_core(cmddat, forkdes, env));
	if ((pid = fork()) == -1)
		return (ft_returnmsg("fork(): Out of resource!", STDERR_FILENO, -1));
	if (pid == 0)
	{
		switch_traps(FALSE);
		exit(exec_core(cmddat, forkdes, env));
	}
	exec_pipe_clean(cmddat);
	if (spid)
		*spid = pid;
	else
		jobnode = sh_job_add(cmddat->c_path, pid, kJobStateRunning);
	if (async)
		return (-1);
	return (ft_wait(jobnode));
}

int			exec_cmd(t_cmdnode *cmddat, int async, pid_t *spid, char **env)
{
	extern char	**g_lvars;
	extern char	**environ;
	char		**tmp;
	uint8_t		is_cmd;

	if (!cmddat)
		return (EXIT_FAILURE);
	is_cmd = (cmddat->builtin || cmddat->c_path);
	if (cmddat->c_vars)
	{
		tmp = cmddat->c_vars;
		while (*tmp)
			set_env_from_str((is_cmd) ? NULL : &g_lvars, *(tmp++));
	}
	if (!is_cmd)
		return (EXIT_SUCCESS);
	return (exec_bincmd(cmddat, async, spid, (env) ? env : environ));
}

/*
**	if (cmddat->builtin)
**		exval = (cmddat->builtin)((int)ft_tablen(cmddat->c_av), cmddat->c_av,
**			(cmddat->stdout_fd == -1) ? STDOUT_FILENO : cmddat->stdout_fd);
**	else
**		exval = exec_bincmd(cmddat, async, spid, (env) ? env : environ);
**	return (exval);
*/
