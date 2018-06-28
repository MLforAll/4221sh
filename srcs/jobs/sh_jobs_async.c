/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs_async.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 16:28:04 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/24 23:38:01 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "sh_jobs.h"

#if SHJBS_LOCK_USE_PTHREADS == TRUE

pthread_mutex_t *g_jobmutex = PTHREAD_MUTEX_INITIALIZER;

void		sh_jobop_lock(void)
{
	(void)pthread_mutex_lock(g_jobmutex);
}

void		sh_jobop_unlock(void)
{
	(void)pthread_mutex_unlock(g_jobmutex);
}

#else

t_uint8			g_jobop = NO;

void		sh_jobop_lock(void)
{
	while (TRUE)
		if (!g_jobop)
			break ;
	g_jobop = YES;
}

void		sh_jobop_unlock(void)
{
	g_jobop = NO;
}

#endif
