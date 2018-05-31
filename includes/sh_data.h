/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_data.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 20:21:10 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/31 04:16:37 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_DATA_H
# define SH_DATA_H

/*
** job control struct
*/

enum			e_jobstate
{
	kJobStateRunning,
	kJobStateStopped,
	kJobStateTerminated
};

typedef struct	s_jobctrl
{
	int				j_idx;
	enum e_jobstate	j_state;
	char			*j_cmd;
	pid_t			j_pid;
}				t_jobctrl;

/*
** errs enum
*/

typedef enum	e_errs
{
	SH_ERR_UNDEFINED,
	SH_ERR_NOCMD,
	SH_ERR_NOENT,
	SH_ERR_NOCD,
	SH_ERR_NOSET,
	SH_ERR_TMARG,
	SH_ERR_PERM,
	SH_ERR_FORK,
	SH_ERR_TMLNK,
	SH_ERR_NOTDIR,
	SH_ERR_NUMARG,
	SH_ERR_INVID,
	SH_ERR_ARGREQ,
	SH_ERR_MAX
}				t_errs;

#endif
