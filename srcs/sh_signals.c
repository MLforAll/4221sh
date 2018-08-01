/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 18:31:09 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/01 19:07:52 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "sh_jobs.h"
#include "sh.h"

/*
** Documentation: Job Control Signals
**
** SIGTTIN -> Bg Process tries to read terminal
** SIGTTOU -> Bg Process tries to write or set terminal
** SIGCHLD -> Parent process receives it when one of its child chgs status
** SIGTSTP -> Stop Signal (Sent by Ctrl-Z)
** SIGCONT -> Continue Signal
*/

void		switch_traps(int ign)
{
	const int		blk_sigs[] = {SIGTTIN, SIGTTOU, SIGTSTP, SIGCONT,
								SIGINT, SIGTERM};
	void			(*act)(int);
	unsigned short	idx;

	idx = 0;
	act = (ign) ? SIG_IGN : SIG_DFL;
	while (idx < (unsigned short)(sizeof(blk_sigs) / sizeof(int)))
		(void)signal(blk_sigs[idx++], act);
	(void)signal(SIGCHLD, (ign) ? &sh_jb_sighdl : SIG_DFL);
}
