/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 02:21:25 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/01 03:17:42 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

void	ft_joblstdel(void *data, size_t datsize)
{
	if (datsize == 0)
		return ;
	free(((t_jobctrl*)data)->j_cmd);
	free(data);
}

void	ft_jobputnode(t_jobctrl *data)
{
	const char	*jobstates[] = {"Running", "Stopped", "Terminated"};

	ft_putchar('[');
	ft_putnbr(data->j_idx);
	ft_putchar(']');
	ft_putchar((data->j_state == kJobStateRunning) ? '+' : '-');
	ft_putchar(' ');
	ft_putstr(jobstates[(int)data->j_state]);
	ft_putchar('\t');
	ft_putendl(data->j_cmd);
}
