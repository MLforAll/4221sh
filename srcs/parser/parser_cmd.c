/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 02:03:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/11 22:47:42 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sh_parser.h"

static void	add_redirect(t_cmdnode *cmddat, t_list **tok, int io_nbr)
{
	t_list		*nr;
	t_redirect	nrdat;

	ft_bzero(&nrdat, sizeof(t_redirect));
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

	cmddat->c_av = ft_tabnew();
	first_word = TRUE;
	io_nbr = 1;
	while (tokens)
	{
		tokdat = (t_token*)tokens->content;
		if (tokdat->type == WORD)
		{
			if (first_word)
			{
				cmddat->c_path = ft_strdup(tokdat->toks);
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
