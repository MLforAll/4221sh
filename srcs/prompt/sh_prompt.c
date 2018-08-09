/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 21:41:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/09 05:36:31 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"

static int	check_str(char **dest, const char **af, char *s)
{
	int			subr;

	subr = FALSE;
	if ((*af = ft_strstart(s, "\\u")))
		subr = add_username(dest);
	else if ((*af = ft_strstart(s, "\\h")))
		subr = add_hostname(dest);
	else if ((*af = ft_strstart(s, "\\w")))
		subr = add_pwd(dest, YES);
	else if ((*af = ft_strstart(s, "\\W")))
		subr = add_pwd(dest, NO);
	else if ((*af = ft_strstart(s, "\\033")))
		subr = ft_stradd(dest, "\033");
	else
	{
		*af = s + 1;
		subr = ft_strnadd(dest, s, 1);
	}
	return (subr);
}

char		*get_prompt_from_str(char *s)
{
	char			*ret;
	const char		*af;

	if (!(ret = ft_strnew(0)))
		return (NULL);
	while (*s)
	{
		if (!check_str(&ret, &af, s))
		{
			ft_strdel(&ret);
			break ;
		}
		s += (af - s);
	}
	return (ret);
}
