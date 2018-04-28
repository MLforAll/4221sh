/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ptrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 06:02:33 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/28 06:25:07 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "bl.h"

t_lexstate	add_to_curr(t_list **ret,
								char **currtok,
								char c,
								t_lexstate curr_state)
{
	(void)ret;
	ft_strnadd(currtok, &c, 1);
	return (curr_state);
}

t_lexstate	add_token_to_ret(t_list **ret,
								char **currtok,
								char c,
								t_lexstate curr_state)
{
	(void)c;
	add_token(ret, *currtok);
	free(*currtok);
	*currtok = ft_strnew(0);
	return (curr_state);
}

t_lexstate	switch_to_dquote(t_list **ret,
								char **currtok,
								char c,
								t_lexstate curr_state)
{
	(void)ret;
	(void)currtok;
	(void)c;
	(void)curr_state;
	return (kLexStateDQuote);
}

t_lexstate	switch_to_general(t_list **ret,
								char **currtok,
								char c,
								t_lexstate curr_state)
{
	(void)ret;
	(void)currtok;
	(void)c;
	(void)curr_state;
	return (kLexStateGeneral);
}
