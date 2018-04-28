/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bl.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 20:14:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/28 06:21:24 by kdumarai         ###   ########.fr       */
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
	kCharStateDQuote
}				t_charstate;

t_list		*lex_line(char *line);

void		add_token(t_list **tokens, char *s);

t_lexstate	add_to_curr(t_list **ret,
								char **currtok,
								char c,
								t_lexstate curr_state);
t_lexstate	add_token_to_ret(t_list **ret,
								char **currtok,
								char c,
								t_lexstate curr_state);
t_lexstate	switch_to_dquote(t_list **ret,
								char **currtok,
								char c,
								t_lexstate curr_state);
t_lexstate	switch_to_general(t_list **ret,
								char **currtok,
								char c,
								t_lexstate curr_state);

#endif
