/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 02:03:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/13 01:06:39 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sh.h"
#include "sh_parser.h"

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

static void	add_redirect(t_cmdnode *cmddat, t_list **tok, int io_nbr)
{
	t_list		*nr;
	t_redirect	nrdat;

	ft_bzero(&nrdat, sizeof(t_redirect));
	nrdat.agreg = -1;
	nrdat.io_nbr = io_nbr;
	nrdat.rtype = ((t_token*)(*tok)->content)->type;
	if ((*tok)->next && ((t_token*)(*tok)->next->content)->type == WORD)
	{
		nrdat.filename = ft_strdup(((t_token*)(*tok)->next->content)->toks);
		*tok = (*tok)->next;
	}
	if (!(nr = ft_lstnew(&nrdat, sizeof(t_redirect))))
		return ;
	ft_lstpush(&cmddat->c_redirects, nr);
}

void		fill_cmd_data(t_cmdnode *cmddat, t_list *tokens)
{
	t_token	*tokdat;
	int		first_word;
	int		io_nbr;

	first_word = TRUE;
	io_nbr = 1;
	while (tokens)
	{
		tokdat = (t_token*)tokens->content;
		if (tokdat->type == WORD)
		{
			if (first_word)
			{
				cmddat->c_path = get_cmd_path(tokdat->toks, NULL);
				first_word = FALSE;
			}
			ft_tabaddstr(&cmddat->c_av, tokdat->toks);
		}
		else if (tokdat->type == IO_NUMBER)
			io_nbr = ft_atoi(tokdat->toks);
		else if (tokdat->type >= GREAT && tokdat->type <= DLESS)
			add_redirect(cmddat, &tokens, io_nbr);
		tokens = tokens->next;
	}
}
