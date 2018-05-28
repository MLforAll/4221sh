/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 23:35:25 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/28 01:26:37 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_BUILTINS_H
# define SH_BUILTINS_H

/*
** utilities
*/

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

int		env_bltn(int ac, char **av, int outfd);
int		setenv_bltn(int ac, char **av, int outfd);
int		unsetenv_bltn(int ac, char **av, int outfd);

#endif
