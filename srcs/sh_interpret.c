/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_interpret.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 18:22:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/12 22:22:37 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"

/*static void	fill_bltn(t_cmd *cmd, char *line_cmd)
{
	char			*nptr;
	unsigned int	idx;
	static int		(*bltns_funcs[])(int, char **, int) = {&echo_bltn,
		&cd_bltn, &exit_bltn, &env_bltn, &setenv_bltn, &unsetenv_bltn,
		&source_bltn, NULL};

	idx = 0;
	nptr = SH_BLTNS;
	while (idx < sizeof(bltns_funcs) / sizeof(*bltns_funcs) && *nptr)
	{
		if (ft_strcmp(line_cmd, nptr) == 0)
		{
			cmd->builtin = bltns_funcs[idx];
			return ;
		}
		nptr += ft_strlen(nptr) + 1;
		idx++;
	}
}*/
