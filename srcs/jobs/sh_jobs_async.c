/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs_async.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 16:28:04 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/21 16:37:36 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "sh_jobs.h"

uint8_t		g_jobop = NO;

void		sh_jobop_lock(void)
{
	assert(!SHJBS_LOCK_USE_PTHREAD);
	while (TRUE)
		if (!g_jobop)
			break ;
	g_jobop = YES;
}

void		sh_jobop_unlock(void)
{
	assert(!SHJBS_LOCK_USE_PTHREAD);
	g_jobop = NO;
}