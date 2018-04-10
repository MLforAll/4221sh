/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 22:31:45 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/10 20:00:24 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh.h"

char			*get_env_var(char **env, const char *var)
{
	char	*ret;

	if (!env || !var)
		return (NULL);
	while (*env)
	{
		if ((ret = ft_strstart(*env, (char*)var)) && *ret == '=')
			return (ret + 1);
		env++;
	}
	return (NULL);
}

char			*chg_env_var(char **env, const char *var, char *new)
{
	char	*tmp;

	if (!env || !var || !new)
		return (NULL);
	while (*env)
	{
		if ((tmp = ft_strstart(*env, (char*)var)) && *tmp == '=')
			break ;
		env++;
	}
	if (!*env)
		return (NULL);
	ft_strdel(env);
	*env = ft_strnew(ft_strlen(var) + ft_strlen(new) + 1);
	ft_strcpy(*env, var);
	ft_strcat(*env, "=");
	ft_strcat(*env, new);
	return (*env);
}

char			*set_env_var(char ***env, const char *var, char *value)
{
	char	*ret;
	char	**old;
	char	*new_entry[2];
	char	*entry_str;
	size_t	newlen;

	if (!env || !var || !value)
		return (NULL);
	if ((ret = chg_env_var(*env, var, value)))
		return (ret);
	if (!(entry_str = ft_strnew(ft_strlen(var) + ft_strlen(value) + 1)))
		return (NULL);
	ft_strcpy(entry_str, var);
	ft_strcat(entry_str, "=");
	ft_strcat(entry_str, value);
	new_entry[0] = entry_str;
	new_entry[1] = NULL;
	old = *env;
	*env = ft_tabjoin((const char**)*env, (const char**)new_entry);
	free(entry_str);
	ft_tabfree(&old);
	newlen = ft_tablen((const char**)*env);
	return ((**env && newlen > 0) ? (*env)[newlen - 1] : NULL);
}

void			del_env_var(char ***env, const char *var)
{
	char	*tmp;
	char	**new_env;
	char	**bw;
	char	**bwn;

	if (!env || !var)
		return ;
	if (!(new_env = (char**)malloc(sizeof(char*) * \
		(ft_tablen((const char**)*env) + 1))))
		return ;
	bwn = new_env;
	bw = *env;
	while (*bw)
	{
		if (!(tmp = ft_strstart(*bw, (char*)var)) || *tmp != '=')
			*(bwn++) = ft_strdup(*bw);
		bw++;
	}
	*bwn = NULL;
	ft_tabfree(env);
	*env = new_env;
}
