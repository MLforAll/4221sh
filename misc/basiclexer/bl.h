/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bl.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 20:14:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/26 22:35:09 by kdumarai         ###   ########.fr       */
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
	kCharStateGeneral,
	kCharStateSpace,
	kCharStateDQuote,
	kCharStateNull
}				t_charstate;

t_list	*lex_line(char *line);

#endif
