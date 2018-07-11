/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 17:30:47 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/11 03:18:55 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARSER_H
# define SH_PARSER_H

# include <stdlib.h>
# include "sh_lexer.h"

# define SH_HEREDOC_PR		"heredoc> "
# define SH_PIPE_PR			"pipe> "
# define SH_ANDIF_PR		"andif> "
# define SH_ORIF_PR			"orif> "

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
	char		*filename;
	int			io_nbr;
	int			agreg;
	t_toktype	rtype;
}				t_redirect;

/*
** parser
*/

char			*parser_check_syntax(t_list *tokens, t_uint8 ragain);
void			parser_check_heredocs(t_list *tokens);
t_uint8			parser_check_inclist(char **line, t_list **tokens);

t_btree			*parse_tokens(char **line, t_list *tokens);

/*
** parser utilities
*/

void			fill_cmd_data(t_cmdnode *cmddat, t_list *tokens);
char			*get_cmd_path(char *line_cmd, char **env);
int				ft_splitquote(t_list **dest, char *s, char *charset, char *cs);
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
