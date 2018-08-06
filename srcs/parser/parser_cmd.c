/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 02:03:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/06 22:28:42 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sh_parser.h"

inline static int		get_dfl_io_nbr(t_toktype type)
{
	return ((type == LESS || type == DLESS) ? STDIN_FILENO : STDOUT_FILENO);
}

static t_uint8			add_redirect(t_cmdnode *cmddat,
									t_dlist **tok,
									int *io_nbr)
{
	t_list		*nr;
	t_token		*nextdat;
	t_redirect	nrdat;
	t_token		*tokdat;

	tokdat = ((t_token*)(*tok)->content);
	ft_bzero(&nrdat, sizeof(t_redirect));
	nrdat.agreg = -1;
	nrdat.io_nbr = (*io_nbr == -1) ? get_dfl_io_nbr(tokdat->type) : *io_nbr;
	nrdat.rtype = tokdat->type;
	if ((*tok)->next)
	{
		nextdat = (t_token*)(*tok)->next->content;
		if (nextdat->type == WORD
			&& (!nextdat->s || !(nrdat.data = ft_strdup(nextdat->s))))
			return (FALSE);
		else if (nextdat->type == IO_NUMBER && nextdat->s)
			nrdat.agreg = ft_atoi(nextdat->s);
		*tok = (*tok)->next;
	}
	*io_nbr = -1;
	if (!(nr = ft_lstnew(&nrdat, sizeof(t_redirect))))
		return (FALSE);
	ft_lstpush(&cmddat->c_redirects, nr);
	return (TRUE);
}

inline static t_uint8	word_action(t_cmdnode *cmddat,
									t_token *tokdat,
									t_uint8 *fw)
{
	if (ft_strchr(tokdat->s, '=') && *fw)
		return ((t_uint8)ft_tabaddstr(&cmddat->c_vars, tokdat->s));
	if (!ft_tabaddstr(&cmddat->c_av, tokdat->s))
		return (FALSE);
	if (!*fw)
		return (TRUE);
	if (!fill_bltn(cmddat, cmddat->c_av[0])
		&& !(cmddat->c_path = get_cmd_path(cmddat->c_av[0], NULL)))
		return (FALSE);
	*fw = FALSE;
	return (TRUE);
}

t_uint8					fill_cmd_data(t_cmdnode *cmddat, t_dlist *tokens)
{
	t_token	*tokdat;
	t_uint8	first_word;
	int		io_nbr;
	t_uint8	status;

	first_word = TRUE;
	io_nbr = -1;
	while (tokens)
	{
		tokdat = (t_token*)tokens->content;
		status = TRUE;
		if (tokdat->type == WORD)
			status = word_action(cmddat, tokdat, &first_word);
		else if (tokdat->type == IO_NUMBER)
			io_nbr = ft_atoi(tokdat->s);
		else if (is_twice_redir(tokens))
			io_nbr = -2;
		else if (tokdat->type >= GREAT && tokdat->type <= DLESS)
			status = add_redirect(cmddat, &tokens, &io_nbr);
		if (!status)
			return (FALSE);
		tokens = tokens->next;
	}
	return (TRUE);
}
