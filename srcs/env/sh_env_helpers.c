/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 18:30:04 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/12 01:52:10 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh.h"

char			*set_env_from_str(char ***env, char *str)
{
	char	*eq;
	char	*var;
	char	*value;
	char	*ret;

	if (!str || !(eq = ft_strchr(str, '=')))
		return (NULL);
	var = ft_strnew(eq - str);
	ft_strncpy(var, str, eq - str);
	value = eq + 1;
	ret = set_env_var(env, (const char*)var, value);
	ft_strdel(&var);
	return (ret);
}

char			*set_env_var_n(char ***env, const char *var, int value)
{
	char	*ret;
	char	*value_str;

	if (!var || !(value_str = ft_itoa(value)))
		return (NULL);
	ret = set_env_var(env, var, value_str);
	ft_strdel(&value_str);
	return (ret);
}
