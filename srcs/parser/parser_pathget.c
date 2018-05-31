/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pathget.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 23:46:20 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/31 04:01:02 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sh.h"

char				*get_cmd_path(char *line_cmd, char **env)
{
	char			*env_path;
	char			**paths;
	char			**tmp;
	char			*ret;

	if (!line_cmd)
		return (NULL);
	if (ft_strchr(line_cmd, '/') || !(env_path = get_env_var(env, "PATH")))
		return (ft_strdup(line_cmd));
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
	return ((!ret) ? ft_strdup(line_cmd) : ret);
}

int					fill_bltn(t_cmdnode *cmddat, char *line_cmd)
{
	int			idx;
	static int	(*bltns_funcs[10])(int, char **, int) = {&echo_bltn,
		&cd_bltn, &exit_bltn, &source_bltn,
		&env_bltn, &setenv_bltn, &unsetenv_bltn,
		&jobs_bltn, &fg_bltn, &bg_bltn};

	if ((idx = sh_get_bltn(NULL, line_cmd)) == -1)
		return (FALSE);
	cmddat->builtin = bltns_funcs[idx];
	return (TRUE);
}
