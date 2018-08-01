/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 20:14:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/01 19:40:47 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_LEXER_H
# define SH_LEXER_H

# include "libft.h"

/*
** Macros
*/

# define LEXER_OK		0
# define LEXER_FAIL		-1
# define LEXER_INC		1
# define LEXER_INCDQ	2
# define LEXER_INCSQ	3

/*
** lexer data types
*/

typedef enum	e_lexstate
{
	kLexStateUndefined,
	kLexStateReadAgain,
	kLexStateGeneral,
	kLexStateDQuote,
	kLexStateSQuote,
	kLexStateAmpersand,
	kLexStateRedirections
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
	kCharAndIf,
	kCharOrIf,
	kCharDash
}				t_charstate;

typedef enum	e_toktype
{
	NONE,
	INCOMPG,
	INCOMPD,
	INCOMPS,
	WORD,
	GREAT,
	DGREAT,
	LESS,
	DLESS,
	IO_NUMBER,
	DASH,
	PIPE,
	SEMI,
	AND_IF,
	OR_IF,
	AMPERSAND,
}				t_toktype;

typedef enum	e_quoting
{
	kQuoteNone,
	kSQuote,
	kDQuote,
	kEscape
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

/*
** ft_switch() requirement
*/

typedef struct	s_equi
{
	int		nb;
	int		(*act)(void *);
	void	*data;
	char	reversed_pad[4];
}				t_equi;

/*
** Lexer main func
*/

int				lex_line(t_dlist **dest, char *line);

/*
** Tokens mgmt
*/

t_uint8			add_token(t_dlist **tokens,
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
int				lex_redirects(void *data);
int				lex_ampersand(void *data);

/*
** State Switchers
*/

int				switch_to_dquote(void *data);
int				switch_to_squote(void *data);

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

t_uint8			lexer_expand_getvar(char **s, t_str *vs);

t_uint8			lexer_expand_var(char **s,
								t_str *vs,
								t_list **ret,
								t_quoting curr);

t_uint8			lexer_expand_tilde(char **s, t_str *vs);

/*
** State functions used throughout
*/

int				lexact_append_current(void *data);
int				lexact_add_token(void *data);
void			lexact_add_io_nbr(t_lexdat *cdat);

t_uint8			create_token_with_buff(t_lexdat *dat, t_toktype type, int prio);

/*
** Utilities
*/

int				ft_swcmp(const void *p1, const void *p2);
void			tokens_lstdel(void *data, size_t datsize);

#endif
