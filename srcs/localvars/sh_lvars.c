/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lvars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 23:54:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/27 20:56:16 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

char	**g_lvars;

char	*get_lvar(const char *var)
{
	return (get_env_var(g_lvars, var));
}

char	*chg_lvar(const char *var, char *new)
{
	return (chg_env_var(g_lvars, var, new));
}

char	*set_lvar(const char *var, char *value)
{
	return (set_env_var(&g_lvars, var, value));
}

void	del_lvar(const char *var)
{
	del_env_var(&g_lvars, var);
}
