/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bl.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 20:14:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/30 15:37:34 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BL_H
# define BL_H

# include "libft.h"

typedef enum	e_lexstate
{
	kLexStateUndefined,
	kLexStateGeneral,
	kLexStateDQuote
}				t_lexstate;

typedef enum	e_charstate
{
	kCharStateNull,
	kCharStateGeneral,
	kCharStateSpace,
	kCharStateDQuote,
	kCharStateRedir,
	kCharStatePipe
}				t_charstate;

typedef enum	e_toktype
{
	kTokTypeNone,
	kTokTypeGeneral,
	kTokTypeIONumber,
	kTokTypeRedir,
	kTokTypePipe
}				t_toktype;

typedef struct	s_equi
{
	int		nb;
	int		(*act)(void *);
	void	*data;
}				t_equi;

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

void			add_token(t_list **tokens, char *s, t_toktype type);

int				add_to_curr(void *data);
int				add_token_to_ret(void *data);
int				create_redir_tok(void *data);
int				create_pipe_tok(void *data);
int				switch_to_dquote(void *data);
int				switch_to_general(void *data);

#endif
