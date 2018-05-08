/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 20:14:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/08 23:18:46 by kdumarai         ###   ########.fr       */
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
}				t_token;

typedef struct	s_lexdat
{
	t_list		**ret;
	char		*currtoks;
	t_lexstate	curr_state;
	char		c;
}				t_lexdat;

t_list			*lex_line(char *line);

int				lex_general(void *data);
int				lex_dquote(void *data);
int				lex_great(void *data);

void			add_token(t_list **tokens, char *s, t_toktype type);

int				add_to_curr(void *data);
int				add_token_to_ret(void *data);

int				switch_to_great(void *data);

int				ft_swcmp(void *p1, void *p2);
t_charstate		get_charstate(char c);

#endif
