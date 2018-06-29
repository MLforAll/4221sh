/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 16:39:19 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/29 03:21:23 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

inline static int	lexer_exp_var_free(char *new, char *var)
{
	free(new);
	free(var);
	return (-1);
}

int					lexer_expand_var(char **s)
{
	char		*new;
	char		*tmp;
	const char	*chr;
	size_t		len;
	char		*var;

	if (!(chr = (const char*)ft_strchr(*s, '$')) || !chr[1])
		return (FALSE);
	len = 0;
	while (ft_isalnum(chr[len + 1]))
		len++;
	if (len == 0)
		return (FALSE);
	var = NULL;
	if (!(new = ft_strndup(*s, chr - (const char*)*s))
		|| !(var = ft_strndup(chr + 1, len)))
		return (lexer_exp_var_free(new, var));
	if (((tmp = get_lvar(var))
		|| (tmp = getenv(var)))
		&& (!ft_stradd(&new, tmp) || !ft_stradd(&new, chr + len + 1)))
		return (lexer_exp_var_free(new, var));
	*s = new;
	free(var);
	return (TRUE);
}

int					lexer_expand_tilde(char **s)
{
	char	*tmp;

	if ((*s)[0] == '~' && (tmp = getenv("HOME"))
		&& (tmp = ft_strjoin(tmp, *s + 1)))
	{
		*s = tmp;
		return (TRUE);
	}
	return (FALSE);
}
