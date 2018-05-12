/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmdexec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 20:09:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/12 02:07:37 by kdumarai         ###   ########.fr       */
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

static int	exec_bincmd(t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		exval;

	exval = 0;
	if ((pid = fork()) == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		prepare_dups(cmd);
		switch_traps(FALSE);
		chg_env_var(env, "_", cmd->c_path);
		execve(cmd->c_path, cmd->c_argv, env);
		exit(exec_shell(cmd->c_path) == EXIT_SUCCESS ? EXIT_SUCCESS : 127);
	}
	cmd->c_pid = pid;
	if (cmd->next)
		return (EXIT_SUCCESS);
	waitpid(pid, &exval, 0);
	if (WIFSIGNALED(exval))
		sh_child_sighandler(WTERMSIG(exval));
	return (WEXITSTATUS(exval));
}

int			exec_cmd(t_cmd *cmd, char **env)
{
	extern char	**environ;
	int			errval;
	int			exval;

	if (cmd->builtin)
		exval = (cmd->builtin)((int)ft_tablen(cmd->c_argv), \
			cmd->c_argv, (cmd->next) ? cmd->c_pfd[1] : STDOUT_FILENO);
	else
	{
		if ((errval = cmd_chk(cmd->c_path)) >= 0)
		{
			if (cmd->prev)
				close(cmd->prev->c_pfd[0]);
			sh_err(errval, NULL, cmd->c_path);
			return (127);
		}
		exval = exec_bincmd(cmd, (env) ? env : environ);
	}
	if (!cmd->next && cmd->c_pfd[0] > 2)
		close(cmd->c_pfd[0]);
	if (cmd->next && cmd->c_pfd[1] > 2)
		close(cmd->c_pfd[1]);
	return (exval);
}

static int	run_cmdp(t_cmd *cmdp)
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
}

int			exec_cmds(char *line)
{
	int		ret;
	t_cmd	*cmdp;
	t_list	*cmds;
	t_list	*bw;

	if (*line == '#')
		return (EXIT_SUCCESS);
	if (!ft_splitquote(&cmds, line, ";", SH_QUOTES))
		return (ft_returnmsg("exec_cmds: line split err!", STDERR_FILENO, 258));
	bw = cmds;
	ret = EXIT_SUCCESS;
	while (bw)
	{
		cmdp = interpret_cmd(bw->content);
		ret = run_cmdp(cmdp);
		ft_cmddel(&cmdp);
		bw = bw->next;
	}
	ft_lstdel(&cmds, &free_tlist);
	return (ret);
}
