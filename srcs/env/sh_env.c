/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 22:31:45 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/21 23:30:02 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh.h"

char			*get_env_var(char **env, const char *var)
{
	extern char	**environ;
	char		*ret;
	char		**bw;

	if (!var)
		return (NULL);
	bw = (env) ? env : environ;
	while (*bw)
	{
		if ((ret = ft_strstart(*bw, (char*)var)) && *ret == '=')
			return (ret + 1);
		bw++;
	}
	return (NULL);
}

char			*chg_env_var(char **env, const char *var, char *new)
{
	extern char	**environ;
	char		*tmp;
	char		**bw;

	if (!var || !new)
		return (NULL);
	bw = (env) ? env : environ;
	while (*bw)
	{
		if ((tmp = ft_strstart(*bw, (char*)var)) && *tmp == '=')
			break ;
		bw++;
	}
	if (!*bw)
		return (NULL);
	ft_strdel(bw);
	*bw = ft_strnew(ft_strlen(var) + ft_strlen(new) + 1);
	ft_strcpy(*bw, var);
	ft_strcat(*bw, "=");
	ft_strcat(*bw, new);
	return (*bw);
}

char			*set_env_var(char ***env, const char *var, char *value)
{
	extern char	**environ;
	char		***tgtenv;
	char		*ret;
	char		*entry_str;
	size_t		newlen;

	if (!var || !value)
		return (NULL);
	tgtenv = (env) ? env : &environ;
	if ((ret = chg_env_var(*tgtenv, var, value)))
		return (ret);
	if (!(entry_str = ft_strnew(ft_strlen(var) + ft_strlen(value) + 1)))
		return (NULL);
	ft_strcpy(entry_str, var);
	ft_strcat(entry_str, "=");
	ft_strcat(entry_str, value);
	ft_tabaddstr(tgtenv, entry_str);
	free(entry_str);
	newlen = ft_tablen(*tgtenv);
	return ((**tgtenv && newlen > 0) ? (*tgtenv)[newlen - 1] : NULL);
}

void			del_env_var(char ***env, const char *var)
{
	extern char	**environ;
	char		***tgtenv;
	char		*tmp;
	char		**new_env;
	char		**bw[2];

	if (!var)
		return ;
	tgtenv = (env) ? env : &environ;
	if (!(new_env = (char**)malloc(sizeof(char*) * \
		(ft_tablen(*tgtenv) + 1))))
		return ;
	bw[0] = new_env;
	bw[1] = *tgtenv;
	while (*bw[1])
	{
		if (!(tmp = ft_strstart(*(bw[1]), (char*)var)) || *tmp != '=')
			*(bw[0]++) = ft_strdup(*(bw[1]));
		bw[1]++;
	}
	*(bw[0]) = NULL;
	ft_tabfree(tgtenv);
	*tgtenv = new_env;
}
