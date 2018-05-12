/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_interpret.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 18:22:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/12 02:02:32 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"

static void	fill_bltn(t_cmd *cmd, char *line_cmd)
{
	char			*nptr;
	unsigned int	idx;
	static int		(*bltns_funcs[])(int, char **, int) = {&echo_bltn,
		&cd_bltn, &exit_bltn, &env_bltn, &setenv_bltn, &unsetenv_bltn,
		&source_bltn, NULL};

	idx = 0;
	nptr = SH_BLTNS;
	while (idx < sizeof(bltns_funcs) / sizeof(*bltns_funcs) && *nptr)
	{
		if (ft_strcmp(line_cmd, nptr) == 0)
		{
			cmd->builtin = bltns_funcs[idx];
			return ;
		}
		nptr += ft_strlen(nptr) + 1;
		idx++;
	}
}

char		*get_cmd_path(char *line_cmd, char **env)
{
	char			*env_path;
	char			**paths;
	char			**tmp;
	char			*ret;

	if (!line_cmd)
		return (NULL);
	if (ft_strchr(line_cmd, '/') || !(env_path = get_env_var(env, "PATH")))
		return (line_cmd);
	paths = ft_strsplit(env_path, ':');
	tmp = paths;
	ret = NULL;
	while (*tmp)
	{
		if ((ret = search_dir_for_file(*tmp, line_cmd)))
			break ;
		tmp++;
	}
	ft_tabfree(&paths);
	return ((!ret) ? line_cmd : ret);
}

static char	**get_cmd_argv(char *s)
{
	char	**ret;
	char	*new_str;
	t_list	*argvlst;
	t_list	*bw;

	if (!s || !ft_splitquote(&argvlst, s, "\t ", SH_QUOTES))
		return (NULL);
	bw = argvlst;
	while (bw)
	{
		new_str = ft_strrmquote((char*)bw->content, SH_QUOTES);
		ft_strdel((char**)&bw->content);
		bw->content = new_str;
		bw = bw->next;
	}
	ret = ft_ltot(argvlst);
	ft_lstdel(&argvlst, &free_tlist);
	return (ret);
}

t_cmd		*interpret_cmd(char *cline)
{
	t_cmd	*ret;
	t_cmd	*new;
	t_list	*psplit;
	t_list	*bw;
	extern char	**environ;

	ret = NULL;
	ft_splitquote(&psplit, cline, "|", SH_QUOTES);
	bw = psplit;
	while (bw)
	{
		new = ft_cmdnew();
		ft_cmdpush(&ret, new);
		if (!(new->c_argv = get_cmd_argv(bw->content)))
		{
			ft_cmddel(&ret);
			break ;
		}
		fill_bltn(new, *new->c_argv);
		new->c_path = (!new->builtin) ? get_cmd_path(*new->c_argv, environ) : NULL;
		if (pipe(new->c_pfd) == -1)
			ft_bzero(new->c_pfd, sizeof(new->c_pfd) / sizeof(int));
		bw = bw->next;
	}
	ft_lstdel(&psplit, &free_tlist);
	return (ret);
}
