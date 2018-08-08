/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 18:30:04 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/08 05:55:22 by kdumarai         ###   ########.fr       */
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
	if (!(var = ft_strnew((size_t)(eq - str))))
		return (NULL);
	(void)ft_strncpy(var, str, (size_t)(eq - str));
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
