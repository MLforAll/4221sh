/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:26:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/31 04:00:51 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

int		sh_get_bltn(char **buff, char *chk)
{
	int			idx;
	static char	*bltn_names[10] = {
		"echo", "cd", "exit", "source",
		"env", "setenv", "unsetenv", "jobs", "fg", "bg"};

	idx = 0;
	while (idx < (int)(sizeof(bltn_names) / sizeof(*bltn_names)))
	{
		if (ft_strequ(chk, bltn_names[idx]))
		{
			if (buff)
				*buff = bltn_names[idx];
			return (idx);
		}
		idx++;
	}
	return (-1);
}
