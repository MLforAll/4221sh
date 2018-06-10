/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 23:35:25 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/10 02:36:12 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_BUILTINS_H
# define SH_BUILTINS_H

/*
** builtins data
*/

# define CD_P_OPT		0x1
# define CD_L_OPT		1 << 1
# define CD_DASH_OPT	1 << 2

/*
** utilities
*/

int		get_bltn_opts(int ac, char **av, int *idx, const char *charset);

int		sh_get_bltn(char **buff, char *chk);
char	*getset_pwd_env(void);

/*
** builtins functions
*/

int		echo_bltn(int ac, char **av, int outfd);
int		exit_bltn(int ac, char **av, int outfd);
int		source_bltn(int ac, char **av, int outfd);
int		cd_bltn(int ac, char **av, int outfd);

int		jobs_bltn(int ac, char **av, int outfd);
int		fg_bltn(int ac, char **av, int outfd);
int		bg_bltn(int ac, char **av, int outfd);

int		env_bltn(int ac, char **av, int outfd);
int		setenv_bltn(int ac, char **av, int outfd);
int		unsetenv_bltn(int ac, char **av, int outfd);

#endif
