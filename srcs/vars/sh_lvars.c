/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lvars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 23:54:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/03 06:00:46 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

char		**g_lvars = NULL;

inline char	*get_lvar(const char *var)
{
	return (get_env_var(g_lvars, var));
}

inline char	*chg_lvar(const char *var, char *new)
{
	return (chg_env_var(g_lvars, var, new));
}

inline char	*set_lvar(const char *var, char *value)
{
	return (set_env_var(&g_lvars, var, value));
}

inline char	*set_lvar_n(const char *var, int value)
{
	return (set_env_var_n(&g_lvars, var, value));
}

inline void	del_lvar(const char *var)
{
	del_env_var(&g_lvars, var);
}
