/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 20:14:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/11 15:37:10 by kdumarai         ###   ########.fr       */
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
	kLexStateGreat,
	kLexStateLess
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
	kCharLess,
	kCharAmpersand
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
	AMPERSAND
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
	char		c;
}				t_lexdat;

t_list			*lex_line(char *line);

/*
** Lexer State functions
*/

int				lex_general(void *data);
int				lex_dquote(void *data);
int				lex_great(void *data);
int				lex_less(void *data);

/*
** State functions used throughout
*/

int				add_to_curr(void *data);
int				add_token_to_ret(void *data);

/*
** State switchers
*/

int				switch_to_great(void *data);
int				switch_to_less(void *data);

/*
** Utilities
*/

void			add_token(t_list **tokens, char *s, t_toktype type, int prio);
int				ft_swcmp(void *p1, void *p2);
t_charstate		get_charstate(char c);
void			tokens_lstdel(void *data, size_t datsize);

#endif
