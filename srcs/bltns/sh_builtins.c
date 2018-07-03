/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:26:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/03 05:50:45 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"
#include "ftrl_dev.h"

static char	*g_bltn_names[] = {
	"echo", "cd", "exit", "source", ".",
	"env", "setenv", "unsetenv", "unset",
	"jobs", "fg", "bg"};

int			sh_get_bltn(char **buff, const char *chk)
{
	int			idx;

	idx = 0;
	while (idx < (int)(sizeof(g_bltn_names) / sizeof(*g_bltn_names)))
	{
		if (ft_strequ(chk, g_bltn_names[idx]))
		{
			if (buff)
				*buff = g_bltn_names[idx];
			return (idx);
		}
		idx++;
	}
	return (-1);
}

t_list		*sh_get_bltn_ac(const char *region)
{
	int			idx;
	t_list		*ret;
	t_acres		*curr_dat;
	t_list		*curr;

	idx = 0;
	ret = NULL;
	while (idx < (int)(sizeof(g_bltn_names) / sizeof(*g_bltn_names)))
	{
		if (ft_strstart(g_bltn_names[idx], region)
			&& (curr_dat = (t_acres*)ft_memalloc(sizeof(t_acres)))
			&& (curr_dat->str = ft_strjoin((const void*)g_bltn_names[idx], " "))
			&& (curr_dat->visible_str = ft_strjoin(curr_dat->str, "(builtin)"))
			&& (curr = ft_lstnew_nomalloc(curr_dat, sizeof(t_acres))))
			ft_lstpush(&ret, curr);
		++idx;
	}
	return (ret);
}
