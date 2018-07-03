/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 18:31:09 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/03 01:27:19 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "sh_jobs.h"
#include "sh.h"

int			free_return(void **data, int retv)
{
	if (data && *data)
	{
		free(*data);
		*data = NULL;
	}
	return (retv);
}

void		switch_traps(int ign)
{
	void	(*act)(int);

	act = (ign) ? SIG_IGN : SIG_DFL;
	signal(SIGINT, act);
	signal(SIGTERM, act);
	signal(SIGTSTP, act);
	signal(SIGCHLD, (ign) ? &sh_jb_sighdl : SIG_DFL);
}
