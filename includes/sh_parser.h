/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 17:30:47 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/01 14:56:02 by kdumarai         ###   ########.fr       */
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
# define RA_ABORT		2
# define RA_EOF			3

# define RA_WHOLE		0b1
# define RA_BEFORE		0b10

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
** parser main
*/

t_btree			*parse_tokens(char **line, t_dlist *tokens, int lret, int fd);
t_btree			*parser_create_ast(t_dlist *tokens);

/*
** read again
*/

char				*read_till_delim(const char *prompt,
									const char *delim,
									t_uint8 opts, int fd);

char			*parser_check_syntax(t_dlist *tokens);
int				parser_check_inclist(char **line, t_dlist **tokens,
									t_dlist *tmp, int fd);
int				parser_check_heredocs(t_dlist *tokens, int fd);
int				parser_check_ret(char **line, t_dlist **tokens,
								const char *delim, int fd);

/*
** parser utilities
*/

void			fill_cmd_data(t_cmdnode *cmddat, t_dlist *tokens);
char			*get_cmd_path(char *line_cmd, char **env);

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
