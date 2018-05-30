/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 16:15:34 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/30 23:39:39 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "sh.h"

inline static void	launch_rc(void)
{
	char		*home;
	char		*rcpath;

	if (!(home = getenv("HOME"))
		|| !(rcpath = get_elem_path(home, SH_RC)))
		return ;
	exec_shell(rcpath);
	free(rcpath);
}

inline static char	*ishell_get_prompt(void)
{
	char		*mshp_entry;
	char		*pr;

	if ((mshp_entry = getenv("SH_PROMPT")) && *mshp_entry)
		pr = get_prompt_from_str(mshp_entry);
	else
		pr = get_prompt_from_str("\\u:\\W$ ");
	return ((pr) ? pr : ft_strdup("21sh-1.0$ "));
}

inline static void	do_history(t_dlist **hist, char *line)
{
	static int	n = 0;

	if (!hist)
		return ;
	if (n >= SH_MAXHIST)
		ftrl_histdellast(hist);
	else
		n++;
	ftrl_histadd(hist, line);
}

inline static void	init_ishell(t_rl_opts *opts, t_dlist **hist)
{
	launch_rc();
	ft_bzero(opts, sizeof(t_rl_opts));
	opts->ac_get_result = &sh_get_acres;
	opts->ac_show_result = &sh_show_acres;
	opts->bell = YES;
	load_history(hist);
}

int					interactive_shell(void)
{
	int			ret[2];
	char		*line;
	char		*prompt;
	t_rl_opts	opts;
	t_dlist		*history;

	ret[0] = EXIT_SUCCESS;
	init_ishell(&opts, &history);
	while ((prompt = ishell_get_prompt()))
	{
		line = ft_readline(prompt, &opts, history);
		ft_strdel(&prompt);
		if (!line)
			break ;
		if (*line)
		{
			if ((ret[1] = eval_line(&line, YES)) != -1)
				ret[0] = ret[1];
			do_history(&history, line);
		}
		ft_strdel(&line);
	}
	write_history(history);
	ft_dlstdel(&history, &ftrl_histdelf);
	return (ret[0]);
}
