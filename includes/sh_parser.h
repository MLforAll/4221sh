/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 17:30:47 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/24 23:49:15 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARSER_H
# define SH_PARSER_H

# include <stdlib.h>
# include "sh_lexer.h"

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
	int		(*builtin)(int, char **, int);
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

uint8_t			parser_check_syntax(t_list *tokens, uint8_t ragain);
void			parser_check_heredocs(t_list *tokens);
uint8_t			parser_check_inclist(char **line, t_list **tokens);

t_btree			*parse_tokens(char **line, t_list *tokens, uint8_t ragain);

/*
** parser utilities
*/

void			fill_cmd_data(t_cmdnode *cmddat, t_list *tokens);
char			*get_cmd_path(char *line_cmd, char **env);
int				ft_splitquote(t_list **dest, char *s, char *charset, char *cs);
char			*ft_strrmquote(char *s, char *cset);

/*
** free function
*/

void			ast_btdel(void *data, size_t datsize);

#endif
