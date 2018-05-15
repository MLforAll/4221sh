/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmdexec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 20:09:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/15 02:56:42 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
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

static void	exec_pipe(t_cmdnode *cmddat)
{
	if (cmddat->stdin_fd != -1)
	{
		close(STDIN_FILENO);
		dup2(cmddat->stdin_fd, STDIN_FILENO);
	}
	if (cmddat->stdout_fd != -1)
	{
		close(STDOUT_FILENO);
		dup2(cmddat->stdout_fd, STDOUT_FILENO);
	}
}

static int	exec_bincmd(t_cmdnode *cmddat, int async, char **env)
{
	pid_t	pid;
	int		exval;

	exval = 0;
	if ((pid = fork()) == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		//prepare_dups(cmd);
		exec_pipe(cmddat);
		exec_redir(cmddat);
		switch_traps(FALSE);
		chg_env_var(env, "_", cmddat->c_path);
		execve(cmddat->c_path, cmddat->c_av, env);
		exit(exec_shell(cmddat->c_path) == EXIT_SUCCESS ? EXIT_SUCCESS : 127);
	}
	//cmd->c_pid = pid;
	if (async)
		return (EXIT_SUCCESS);
	waitpid(pid, &exval, 0);
	if (WIFSIGNALED(exval))
		sh_child_sighandler(WTERMSIG(exval));
	return (WEXITSTATUS(exval));
}

int			exec_cmd(t_cmdnode *cmddat, int async, char **env)
{
	extern char	**environ;
	int			errval;
	int			exval;

	if (!cmddat)
		return (EXIT_SUCCESS);
	/*if (cmd->builtin)
		exval = (cmd->builtin)((int)ft_tablen(cmd->c_argv), \
			cmd->c_argv, (cmd->next) ? cmd->c_pfd[1] : STDOUT_FILENO);
	else
	{*/
		if ((errval = cmd_chk(cmddat->c_path)) >= 0)
		{
			sh_err(errval, NULL, cmddat->c_path);
			return (127);
		}
		exval = exec_bincmd(cmddat, async, (env) ? env : environ);
	//}
	return (exval);
}

/*static int	run_cmdp(t_cmd *cmdp)
{
	int		ret;
	t_cmd	*cbw;

	if (!cmdp)
		return (EXIT_SUCCESS);
	cbw = cmdp;
	while (cbw)
	{
		ret = exec_cmd(cbw, NULL);
		if (!cbw->next)
			break ;
		cbw = cbw->next;
	}
	if (!cmdp->next)
		return (ret);
	if (cbw)
		cbw = cbw->prev;
	while (cbw)
	{
		kill(cbw->c_pid, SIGTERM);
		waitpid(cbw->c_pid, NULL, 0);
		cbw = cbw->prev;
	}
	return (ret);
}*/
