/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 17:30:47 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/13 02:42:21 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARSER_H
# define SH_PARSER_H

#include "sh_lexer.h"

/*
** data types
*/

typedef struct	s_astnode
{
	void		*data;
	t_toktype	type;
}				t_astnode;

typedef	struct	s_cmdnode
{
	char	*c_path;
	char	**c_av;
	t_list	*c_redirects;
	int		stdout_fd;
	int		stdin_fd;
}				t_cmdnode;

typedef struct	s_redirect
{
	int			io_nbr;
	t_toktype	rtype;
	char		*filename;
	int			agreg;
}				t_redirect;

/*
** parser
*/

t_btree	*parse_tokens(t_list *tokens);

/*
** parser utilities
*/

void	fill_cmd_data(t_cmdnode *cmddat, t_list *tokens);
char	*get_cmd_path(char *line_cmd, char **env);
int		ft_splitquote(t_list **dest, char *s, char *charset, char *cs);
char	*ft_strrmquote(char *s, char *cset);

/*
** free functions
*/

void	astputelem(void *data, size_t datsize);
void	ast_btdel(void *data, size_t datsize);
void	lstdelf(void *data, size_t datsize);

#endif
