/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 20:14:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/21 07:00:49 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_LEXER_H
# define SH_LEXER_H

# include "libft.h"

/*
** ft_switch requirement
*/

typedef struct	s_equi
{
	int		nb;
	int		(*act)(void *);
	void	*data;
}				t_equi;

/*
** lexer data types
*/

typedef enum	e_lexstate
{
	kLexStateUndefined,
	kLexStateGeneral,
	kLexStateDQuote,
	kLexStateSQuote,
	kLexStateAmpersand,
}				t_lexstate;

typedef enum	e_charstate
{
	kCharNull,
	kCharGeneral,
	kCharSpace,
	kCharTab,
	kCharDQuote,
	kCharSQuote,
	kCharEscape,
	kCharPipe,
	kCharSemi,
	kCharGreat,
	kCharDGreat,
	kCharLess,
	kCharDLess,
	kCharAmpersand,
	kCharDash
}				t_charstate;

typedef enum	e_toktype
{
	NONE,
	INCOMPLETE,
	WORD,
	IO_NUMBER,
	PIPE,
	SEMI,
	AND_IF,
	OR_IF,
	GREAT,
	DGREAT,
	LESS,
	DLESS,
	CLOBBER,
	AMPERSAND,
	DASH
}				t_toktype;

typedef enum	e_quoting
{
	kQuoteNone,
	kSQuote,
	kDQuote
}				t_quoting;

typedef struct	s_token
{
	char			*s;
	int				priority;
	t_toktype		type;
}				t_token;

typedef struct	s_lexdat
{
	t_dlist			**ret;
	char			**linep;
	t_str			currtoks;
	size_t			jmp;
	t_lexstate		curr_state;
	t_charstate		cs;
}				t_lexdat;

int				lex_line(t_dlist **dest, char *line);

/*
** Tokens mgmt
*/

void			add_token(t_dlist **tokens,
						t_str *vs,
						t_toktype type,
						int prio);

/*
** Lexer State functions
*/

int				lex_general(void *data);
int				lex_dquote(void *data);
int				lex_squote(void *data);
int				lex_less(void *data);
int				lex_ampersand(void *data);

/*
** Tokens creators
*/

int				create_great_tok(void *data);
int				create_dgreat_tok(void *data);
int				create_less_tok(void *data);
int				create_dless_tok(void *data);
int				create_pipe_tok(void *data);
int				create_semi_tok(void *data);

/*
** Expansion
*/

int				lexer_expand_var(char **s);
int				lexer_expand_tilde(char **s);

/*
** State functions used throughout
*/

int				lexact_append_current(void *data);
int				lexact_add_token(void *data);
void			lexact_add_io_nbr(t_lexdat *cdat);

/*
** State switchers
*/

int				switch_to_great(void *data);
int				switch_to_less(void *data);
int				switch_to_ampersand(void *data);

/*
** Utilities
*/

int				ft_swcmp(void *p1, void *p2);
void			tokens_lstdel(void *data, size_t datsize);

#endif
