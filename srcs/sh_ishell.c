/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 16:15:34 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/25 04:53:09 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libftreadline.h"
#include "sh.h"

static void	launch_rc(void)
{
	char		*home;
	char		*rcpath;

	if (!(home = getenv("HOME")))
		return ;
	if (!(rcpath = ft_strnew(ft_strlen(home) + ft_strlen(SH_RC) + 1)))
		return ;
	ft_strcpy(rcpath, home);
	ft_strcat(rcpath, "/");
	ft_strcat(rcpath, SH_RC);
	exec_shell(rcpath);
	free(rcpath);
}

static char	*ishell_get_prompt(void)
{
	char		*mshp_entry;
	char		*pr;

	if ((mshp_entry = getenv("SH_PROMPT")) && *mshp_entry)
		pr = get_prompt_from_str(mshp_entry);
	else
		pr = get_prompt_from_str("\\u:\\W$ ");
	return ((pr) ? pr : ft_strdup("21sh-1.0$ "));
}

static void	do_history(t_rl_hist **hist, char *line)
{
	static int	n = 0;

	if (!hist || !line)
		return ;
	if (n >= SH_MAXHIST)
	{
		ft_histdel(hist);
		n = 0;
		return ;
	}
	if (!*line)
		return ;
	ft_histadd(hist, line);
	n++;
}

int			interactive_shell(void)
{
	int			ret;
	char		*line;
	char		*prompt;
	t_rl_opts	opts;
	t_rl_hist	*history;

	history = NULL;
	ret = EXIT_SUCCESS;
	launch_rc();
	ft_bzero(&opts, sizeof(t_rl_opts));
	opts.ac_get_result = &sh_get_acres;
	opts.bell = YES;
	while (42)
	{
		prompt = ishell_get_prompt();
		line = ft_readline(prompt, &opts, history);
		ft_strdel(&prompt);
		if (!line)
			break ;
		if (*line)
			ret = eval_line(&line, YES);
		do_history(&history, line);
		ft_strdel(&line);
	}
	ft_histdel(&history);
	return (ret);
}
