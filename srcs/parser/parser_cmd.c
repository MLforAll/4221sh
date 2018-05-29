/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 02:03:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/28 23:50:54 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sh_parser.h"

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

inline static int	word_action(t_cmdnode *cmddat, t_token *tokdat, uint8_t *fw)
{
	if (ft_strchr(tokdat->toks, '=') && *fw)
		return (ft_tabaddstr(&cmddat->c_vars, tokdat->toks));
	if (!ft_tabaddstr(&cmddat->c_av, tokdat->toks))
		return (FALSE);
	if (!*fw)
		return (TRUE);
	if (!fill_bltn(cmddat, cmddat->c_av[0])
		&& !(cmddat->c_path = get_cmd_path(cmddat->c_av[0], NULL)))
		return (FALSE);
	*fw = FALSE;
	return (TRUE);
}

void				fill_cmd_data(t_cmdnode *cmddat, t_list *tokens)
{
	t_token	*tokdat;
	uint8_t	first_word;
	int		io_nbr;

	first_word = TRUE;
	io_nbr = -1;
	while (tokens)
	{
		tokdat = (t_token*)tokens->content;
		if (tokdat->type == WORD)
			word_action(cmddat, tokdat, &first_word);
		else if (tokdat->type == IO_NUMBER)
			io_nbr = ft_atoi(tokdat->toks);
		else if (tokdat->type >= GREAT && tokdat->type <= DLESS)
			add_redirect(cmddat, &tokens, &io_nbr);
		tokens = tokens->next;
	}
}
