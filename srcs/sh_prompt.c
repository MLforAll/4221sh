/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 21:41:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/10 20:00:39 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"

static int	check_str(char **dest, char **af, char *s, char **env)
{
	int			subr;

	subr = FALSE;
	if ((*af = ft_strstart(s, "\\u")))
		subr = add_username(dest);
	else if ((*af = ft_strstart(s, "\\h")))
		subr = add_hostname(dest);
	else if ((*af = ft_strstart(s, "\\w")))
		subr = add_pwd(dest, YES, env);
	else if ((*af = ft_strstart(s, "\\W")))
		subr = add_pwd(dest, NO, env);
	else if ((*af = ft_strstart(s, "\\033")))
		subr = ft_stradd(dest, "\033");
	else
	{
		*af = s + 1;
		subr = ft_strnadd(dest, s, 1);
	}
	return (subr);
}

char		*get_prompt_from_str(char *s, char **env)
{
	char			*ret;
	char			*af;
	int				subr;

	ret = ft_strnew(0);
	while (*s)
	{
		subr = check_str(&ret, &af, s, env);
		if (!subr)
		{
			ft_strdel(&ret);
			break ;
		}
		s += (af - s);
	}
	return (ret);
}
