/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_data.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 20:21:10 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/06 05:54:34 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_DATA_H
# define SH_DATA_H

/*
** errs enum
** ---------
**
** Nothing else to say.
** SH_ERR_MAX is useless. Do not pass it to sh_err() or sh_err_ret().
** Neither function would return it as well.
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
	SH_ERR_NOJOB,
	SH_ERR_BADFD,
	SH_ERR_MALLOC,
	SH_ERR_BADFILE,
	SH_ERR_FATAL,
	SH_ERR_MAX
}				t_errs;

/*
** bakfds struct
** -------------
**
** Used to backup file descriptions
** for redirections with builtins.
**
** bak: fd of duped output (like stdout)
** orig: output fd
**
** example: backup of stdout
** 		- bak: 3
**		- orig: 1
*/

typedef struct	s_bakfds
{
	int		bak;
	int		orig;
}				t_bakfds;

#endif
