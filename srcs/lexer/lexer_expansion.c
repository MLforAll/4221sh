/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 16:39:19 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/27 05:21:00 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

static t_uint8	lexer_expand_getvar(char **s, t_str *vs)
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

static t_uint8	lexer_expand_var_splt(char **splt, t_str *vs, t_list **ret)
{
	char	**bw;
	t_list	*new;

	bw = splt;
	while (*bw)
	{
		if (!ft_tstrcat(vs, *bw))
			break ;
		if (*(bw + 1))
		{
			if (!(new = ft_lstnew(vs->s, vs->len + 1)))
				break ;
			ft_lstpush(ret, new);
			ft_tstrclr(vs);
		}
		bw++;
	}
	return (*bw == NULL);
}

t_uint8			lexer_expand_var(char **s,
								t_str *vs,
								t_list **ret,
								t_quoting curr)
{
	t_str	exp;
	char	**splt;
	t_uint8	rval;

	if (curr != kQuoteNone)
		return (lexer_expand_getvar(s, vs));
	if (!ft_tstrnew(&exp))
		return (FALSE);
	if (lexer_expand_getvar(s, &exp) && (splt = ft_strsplit(exp.s, ' ')))
	{
		rval = lexer_expand_var_splt(splt, vs, ret);
		ft_tabfree(&splt);
	}
	else
		rval = FALSE;
	ft_tstrdel(&exp);
	return (rval);
}

t_uint8			lexer_expand_tilde(char **s, t_str *vs)
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
