/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 16:39:19 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/22 02:19:03 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

t_uint8				lexer_expand_var(char **s, t_str *vs)
{
	char		*tmp;
	size_t		len;
	char		*var;

	len = 1;
	while (ft_isalnum((*s)[len]) || (*s)[len] == '?')
		len++;
	if (--len == 0)
		return (FALSE);
	var = NULL;
	if (!(var = ft_strndup(*s + 1, len)))
		return (FALSE);
	if (((tmp = get_lvar(var))
		|| (tmp = getenv(var))) && !ft_tstrcat(vs, tmp))
	{
		free(var);
		return (FALSE);
	}
	*s += len;
	free(var);
	return (TRUE);
}

t_uint8				lexer_expand_tilde(char **s, t_str *vs)
{
	char	*tmp;

	if ((*s)[0] == '~' && (tmp = getenv("HOME")))
	{
		if (!ft_tstrcpy(vs, tmp))
			return (FALSE);
		*s += 1;
		return (TRUE);
	}
	return (FALSE);
}
