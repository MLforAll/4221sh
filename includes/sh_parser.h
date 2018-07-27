/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 17:30:47 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/27 05:54:32 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARSER_H
# define SH_PARSER_H

# include <stdlib.h>
# include "sh_lexer.h"

/*
** Macros
*/

# define PARSER_FAIL	258

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
	char	**c_vars;
	int		(*builtin)(int, char **);
	char	*c_path;
	char	**c_av;
	t_list	*c_redirects;
	int		stdout_fd;
	int		stdin_fd;
	int		pfd[2];
}				t_cmdnode;

typedef struct	s_redirect
{
	char		*data;
	int			io_nbr;
	int			agreg;
	t_toktype	rtype;
}				t_redirect;

/*
** parser
*/

char			*parser_check_syntax(t_dlist *tokens);
t_uint8			parser_check_inclist(char **line, t_dlist **tokens,
									t_dlist *tmp);
int				parser_check_heredocs(t_dlist *tokens, t_uint8 ragain);
t_uint8			parser_check_ret(char **line,
								t_dlist **tokens,
								const char *prompt,
								const char *delim);

t_btree			*parser_create_ast(t_dlist *tokens);
t_btree			*parse_tokens(char **line, t_dlist *tokens, int lex_ret);

/*
** parser utilities
*/

void			fill_cmd_data(t_cmdnode *cmddat, t_dlist *tokens);
char			*get_cmd_path(char *line_cmd, char **env);
int				ft_splitquote(t_dlist **dest, char *s, char *charset, char *cs);
char			*ft_strrmquote(char *s, char *cset);

/*
** get cmd paths and builtins
*/

char			*get_cmd_path(char *line_cmd, char **env);
int				fill_bltn(t_cmdnode *cmddat, char *line_cmd);

/*
** free function
*/

void			ast_btdel(void *data, size_t datsize);

#endif
