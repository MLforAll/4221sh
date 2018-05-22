/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 02:03:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/21 23:31:32 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sh.h"
#include "sh_parser.h"

static int			fill_bltn(t_cmdnode *cmddat, char *line_cmd)
{
	char			*nptr;
	unsigned int	idx;
	static int		(*bltns_funcs[8])(int, char **, int) = {&echo_bltn,
		&cd_bltn, &exit_bltn, &env_bltn, &setenv_bltn, &unsetenv_bltn,
		&source_bltn, NULL};

	idx = 0;
	nptr = SH_BLTNS;
	while (idx < sizeof(bltns_funcs) / sizeof(*bltns_funcs) && *nptr)
	{
		if (ft_strcmp(line_cmd, nptr) == 0)
		{
			cmddat->builtin = bltns_funcs[idx];
			return (TRUE);
		}
		nptr += ft_strlen(nptr) + 1;
		idx++;
	}
	return (FALSE);
}

char				*get_cmd_path(char *line_cmd, char **env)
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

inline static int	get_dfl_io_nbr(t_toktype type)
{
	return ((type == LESS || type == DLESS) ? STDIN_FILENO : STDOUT_FILENO);
}

static void			add_redirect(t_cmdnode *cmddat, t_list **tok, int *io_nbr)
{
	t_list		*nr;
	t_redirect	nrdat;
	t_token		*tokdat;

	tokdat = ((t_token*)(*tok)->content);
	ft_bzero(&nrdat, sizeof(t_redirect));
	nrdat.agreg = -1;
	nrdat.io_nbr = (*io_nbr == -1) ? get_dfl_io_nbr(tokdat->type) : *io_nbr;
	nrdat.rtype = tokdat->type;
	if ((*tok)->next)
	{
		if (((t_token*)(*tok)->next->content)->type == WORD)
			nrdat.filename = ft_strdup(((t_token*)(*tok)->next->content)->toks);
		else if (((t_token*)(*tok)->next->content)->type == IO_NUMBER)
			nrdat.agreg = ft_atoi(((t_token*)(*tok)->next->content)->toks);
		*tok = (*tok)->next;
	}
	*io_nbr = -1;
	if (!(nr = ft_lstnew(&nrdat, sizeof(t_redirect))))
		return ;
	ft_lstpush(&cmddat->c_redirects, nr);
}

void				fill_cmd_data(t_cmdnode *cmddat, t_list *tokens)
{
	t_token	*tokdat;
	int		first_word;
	int		io_nbr;

	first_word = TRUE;
	io_nbr = -1;
	while (tokens)
	{
		tokdat = (t_token*)tokens->content;
		if (tokdat->type == WORD)
		{
			ft_tabaddstr(&cmddat->c_av, tokdat->toks);
			if (first_word)
			{
				if (!fill_bltn(cmddat, cmddat->c_av[0]))
					cmddat->c_path = get_cmd_path(cmddat->c_av[0], NULL);
				first_word = FALSE;
			}
		}
		else if (tokdat->type == IO_NUMBER)
			io_nbr = ft_atoi(tokdat->toks);
		else if (tokdat->type >= GREAT && tokdat->type <= DLESS)
			add_redirect(cmddat, &tokens, &io_nbr);
		tokens = tokens->next;
	}
}