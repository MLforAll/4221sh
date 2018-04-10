/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 16:15:34 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/10 20:00:42 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_readline.h"
#include "sh.h"

static void	launch_rc(char ***env)
{
	char		*home;
	char		*rcpath;

	if (!(home = get_env_var(*env, "HOME")))
		return ;
	if (!(rcpath = ft_strnew(ft_strlen(home) + ft_strlen(SH_RC) + 1)))
		return ;
	ft_strcpy(rcpath, home);
	ft_strcat(rcpath, "/");
	ft_strcat(rcpath, SH_RC);
	exec_shell(rcpath, env);
	free(rcpath);
}

static char	*ishell_get_prompt(char **env)
{
	char		*mshp_entry;
	char		*pr;

	if ((mshp_entry = get_env_var(env, "MSH_PROMPT")) && *mshp_entry)
		pr = get_prompt_from_str(mshp_entry, env);
	else
		pr = get_prompt_from_str("\\u:\\W$ ", env);
	return ((pr) ? pr : ft_strdup("msh-1.0$ "));
}

static void	do_history(t_history **hist, int *n, char *line)
{
	if (!hist || !n)
		return ;
	if (*n >= SH_MAXHIST)
	{
		ft_histdel(hist);
		*n = 0;
		return ;
	}
	if (line && *line)
	{
		ft_histadd(hist, line);
		(*n)++;
	}
}

int			interactive_shell(char ***env)
{
	int			ret;
	char		*line;
	char		*prompt;
	t_history	*history;
	int			n;

	prompt = NULL;
	history = NULL;
	n = 0;
	ret = EXIT_SUCCESS;
	launch_rc(env);
	while (42)
	{
		prompt = ishell_get_prompt(*env);
		line = ft_readline(prompt, *env, history);
		do_history(&history, &n, line);
		ft_strdel(&prompt);
		if (!line)
			break ;
		ret = exec_cmds(line, env);
		set_env_var_n(env, "?", ret);
		ft_strdel(&line);
	}
	ft_histdel(&history);
	return (ret);
}
