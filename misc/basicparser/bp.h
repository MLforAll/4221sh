/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bp.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 17:30:47 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/11 02:53:41 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BP_H
# define BP_H

#include "../basiclexer/sh_lexer.h"

typedef struct	s_astnode
{
	void		*data;
	t_toktype	type;
}				t_astnode;

typedef	struct	s_cmdnode
{
	char	*c_path;
	char	**c_av;
	t_list	*redirects;
}				t_cmdnode;

typedef struct	s_redirect
{
	int			io_nbr;
	t_toktype	rtype;
	char		*filename;
	int			agreg;
}				t_redirect;

t_btree	*parse_tokens(t_list *tokens);
void	fill_cmd_data(t_cmdnode *cmddat, t_list *tokens);
void	lstdelf(void *data, size_t datsize);
void	astputelem(void *data, size_t datsize);

#endif
