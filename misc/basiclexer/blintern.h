/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blintern.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 22:48:47 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/11 01:43:55 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLINTERN_H
# define BLINTERN_H

const char	*g_typedesc[13] = {"NONE", "WORD", "IO_NUMBER", "PIPE", "SEMI",
								"AND_IF", "OR_IF", "GREAT", "DGREAT", "LESS",
								"DLESS", "CLOBBER", "AMPERSAND"};

void		print_tokens(char *line);

#endif
