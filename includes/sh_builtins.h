/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 23:35:25 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/30 16:18:42 by kdumarai         ###   ########.fr       */
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

int		get_bltn_opts(char **av, int *idx, const char *charset,
						const char *overrides);

int		sh_get_bltn(char **buff, const char *chk);
t_list	*sh_get_bltn_ac(const char *region);

char	*get_newpath(char *curr, char *path);
char	*getset_pwd_env(void);

/*
** builtins functions
*/

int		echo_bltn(int ac, char **av);
int		exit_bltn(int ac, char **av);
int		source_bltn(int ac, char **av);
int		cd_bltn(int ac, char **av);

int		jobs_bltn(int ac, char **av);
int		fg_bltn(int ac, char **av);
int		bg_bltn(int ac, char **av);

int		env_bltn(int ac, char **av);
int		setenv_bltn(int ac, char **av);
int		unsetenv_bltn(int ac, char **av);

#endif
