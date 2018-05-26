/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 20:14:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/26 09:26:16 by kdumarai         ###   ########.fr       */
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
	WORD,
	IO_NUMBER,
	PIPE,
	SEMI,
	AND_IF,
	AND_OR,
	GREAT,
	DGREAT,
	LESS,
	DLESS,
	CLOBBER,
	AMPERSAND,
	DASH
}				t_toktype;

typedef struct	s_token
{
	char		*toks;
	t_toktype	type;
	int			priority;
}				t_token;

typedef struct	s_lexdat
{
	t_list		**ret;
	char		*currtoks;
	t_lexstate	curr_state;
	t_charstate	cs;
	char		c;
}				t_lexdat;

t_list			*lex_line(char *line);

/*
** Lexer State functions
*/

int				lex_general(void *data);
int				lex_dquote(void *data);
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
** State functions used throughout
*/

int				add_to_curr(void *data);
int				add_token_to_ret(void *data);
void			add_io_nbr(t_lexdat *cdat);

/*
** State switchers
*/

int				switch_to_great(void *data);
int				switch_to_less(void *data);
int				switch_to_ampersand(void *data);

/*
** Utilities
*/

void			add_token(t_list **tokens, char *s, t_toktype type, int prio);
int				ft_swcmp(void *p1, void *p2);
void			tokens_lstdel(void *data, size_t datsize);

#endif
