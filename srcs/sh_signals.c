/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 18:31:09 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/16 17:04:03 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "sh_jobs.h"
#include "sh.h"

void		switch_traps(int ign)
{
	void	(*act)(int);

	act = (ign) ? SIG_IGN : SIG_DFL;
	(void)signal(SIGINT, act);
	(void)signal(SIGTERM, act);
	(void)signal(SIGTSTP, act);
	(void)signal(SIGCHLD, (ign) ? &sh_jb_sighdl : SIG_DFL);
}
