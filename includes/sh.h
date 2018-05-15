/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 01:57:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/14 14:43:42 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include "libft.h"
# include "sh_data.h"
# include "sh_prompt.h"
# include "sh_lexer.h"
# include "sh_parser.h"

/*
** macros
*/

# define SH_NAME			"21sh"
# define SH_PLAIN_PROMPT	SH_NAME "$ "
# define SH_RC				".21shrc"
# define SH_MAXHIST			100
# define SH_BLTNS			"echo\0cd\0exit\0env\0setenv\0unsetenv\0source\0"

# define SH_DEFAULT_PATH	"/usr/local/bin:/usr/bin:/bin:/usr/sbin:" \
							"/opt/X11/bin"

/*
** shell types
*/

int		exec_shell(const char *path);
int		interactive_shell(void);

/*
** cmd exec
*/

void	exec_redir(t_cmdnode *cmddat);
int		exec_cmd(t_cmdnode *cmddat, int async, char **env);
int		eval_line(char *line);

/*
** builtins
*/

int		echo_bltn(int ac, char **av, int outfd);
int		exit_bltn(int ac, char **av, int outfd);

char	*getset_pwd_env(void);
int		cd_bltn(int ac, char **av, int outfd);

int		env_bltn(int ac, char **av, int outfd);
int		setenv_bltn(int ac, char **av, int outfd);
int		unsetenv_bltn(int ac, char **av, int outfd);
int		source_bltn(int ac, char **av, int outfd);

/*
** fsexp utilities
*/

char	*get_basedir(const char *f_path);
char	*search_dir_for_file(const char *d_path, const char *name);
t_list	*search_files_begin(const char *f_path, const char *s_dir, int exec);

/*
** env mgmt
*/

char	*get_env_var(char **env, const char *var);
char	*chg_env_var(char **env, const char *var, char *new);
char	*set_env_var(char ***env, const char *var, char *value);
void	del_env_var(char ***env, const char *var);

char	*set_env_from_str(char ***env, char *str);
char	*set_env_var_n(char ***env, const char *var, int value);

/*
** errors
*/

int		sh_err(int errc, const char *bltn, const char *path);
int		sh_err_ret(int errc, const char *bltn, const char *path, int retv);
void	sh_child_sighandler(int sigc);
int		get_errcode_for_path(const char *path, int mode, int dir);

/*
** misc functions / utilities
*/

int		ft_strchrf(char *s, char c);
char	*get_last_component(const char *str, char c);
char	*get_name_from_path(const char *path);
char	*get_name_from_path_2(const char *path);

int		free_return(void **data, int retv);
void	switch_traps(int ign);
void	prepare_dups(t_cmd *cmd);

t_cmd	*ft_cmdnew(void);
void	ft_cmdpush(t_cmd **headref, t_cmd *new);
void	ft_cmddel(t_cmd **headref);
void	ft_cmddelone(t_cmd **cmdref);

void	free_tlist(void *content, size_t size);
void	ft_lstrmdups(t_list **lst);
int		ft_lstsortalpha(t_list *a, t_list *b);

#endif
