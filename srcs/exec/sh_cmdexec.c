/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmdexec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 20:09:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/26 02:45:14 by kdumarai         ###   ########.fr       */
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

static int	exec_core(t_cmdnode *cmddat, char **env)
{
	int		errval;

	exec_pipe(cmddat);
	exec_redir(cmddat);
	if (cmddat->builtin)
		return ((cmddat->builtin)((int)ft_tablen(cmddat->c_av), cmddat->c_av,
			STDOUT_FILENO));
	chg_env_var(env, "_", cmddat->c_path);
	execve(cmddat->c_path, cmddat->c_av, env);
	if ((errval = cmd_chk(cmddat->c_path)) >= 0)
		return (sh_err_ret(errval, NULL, cmddat->c_path, 127));
	return ((exec_shell(cmddat->c_path) == EXIT_SUCCESS) ? EXIT_SUCCESS : 127);
}

static int	exec_bincmd(t_cmdnode *cmddat, int async, pid_t *spid, char **env)
{
	uint8_t	forkdes;
	pid_t	pid;
	t_list	**jobnode;

	if (!(forkdes = (async || spid || cmddat->c_path)))
		return (exec_core(cmddat, env));
	if ((pid = fork()) == -1)
		return (ft_returnmsg("fork(): Out of resource!", STDERR_FILENO, -1));
	if (pid == 0)
	{
		switch_traps(FALSE);
		exit(exec_core(cmddat, env));
	}
	exec_pipe_clean(cmddat);
	if (spid)
		*spid = pid;
	else
		jobnode = sh_job_add(cmddat->c_path, pid);
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
	//int			exval;

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
	/*if (cmddat->builtin)
		exval = (cmddat->builtin)((int)ft_tablen(cmddat->c_av), cmddat->c_av,
			(cmddat->stdout_fd == -1) ? STDOUT_FILENO : cmddat->stdout_fd);
	else
		exval = exec_bincmd(cmddat, async, spid, (env) ? env : environ);
	return (exval);*/
	return (exec_bincmd(cmddat, async, spid, (env) ? env : environ));
}
