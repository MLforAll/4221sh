/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs_async.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 16:28:04 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/31 22:56:53 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "sh_jobs.h"

#ifdef SHJBS_LOCK_USE_PTHREADS

static pthread_mutex_t g_jobmutex = PTHREAD_MUTEX_INITIALIZER;

inline void				sh_jobop_lock(void)
{
	(void)pthread_mutex_lock(&g_jobmutex);
}

inline void				sh_jobop_unlock(void)
{
	(void)pthread_mutex_unlock(&g_jobmutex);
}

#else

volatile static t_uint8	g_jobop = NO;

inline void				sh_jobop_lock(void)
{
	while (TRUE)
		if (!g_jobop)
			break ;
	g_jobop = YES;
}

inline void				sh_jobop_unlock(void)
{
	g_jobop = NO;
}

#endif
