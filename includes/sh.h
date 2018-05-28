/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 01:57:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/28 02:00:59 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include "libft.h"
# include "libftreadline.h"
# include "sh_data.h"
# include "sh_prompt.h"
# include "sh_builtins.h"
# include "sh_lexer.h"
# include "sh_parser.h"

/*
** macros
*/

# define SH_NAME			"21sh"
# define SH_PLAIN_PROMPT	SH_NAME "$ "
# define SH_RC				".21shrc"
# define SH_MAXHIST			100

# define SH_DEFAULT_PATH	"/usr/local/bin:/usr/bin:/bin:/usr/sbin"

# define SH_HEREDOC_PR		"heredoc> "
# define SH_PIPE_PR			"pipe> "
# define SH_ANDIF_PR		"andif> "
# define SH_ORIF_PR			"orif> "

/*
** shell types
*/

int		exec_shell(const char *path);
int		interactive_shell(void);

/*
** cmd exec
*/

void	exec_redir(t_cmdnode *cmddat);
int		exec_cmd(t_cmdnode *cmddat, int async, pid_t *spid, char **env);
int		eval_line(char **line, uint8_t ragain);

/*
** autocompletion
*/

t_list	*sh_get_acres(char *line, t_cursor *csr);
char	*sh_show_acres(t_list **chs);

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
** local vars mgmt
*/

char	*get_lvar(const char *var);
char	*chg_lvar(const char *var, char *new);
char	*set_lvar(const char *var, char *value);
void	del_lvar(const char *var);

/*
** errors
*/

int		sh_err(int errc, const char *bltn, const char *path);
int		sh_err_ret(int errc, const char *bltn, const char *path, int retv);
void	sh_child_signaled(int sigc);
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

void	free_tlist(void *content, size_t size);
void	ft_lstrmdups(t_list **lst);
int		ft_lstsortalpha(t_list *a, t_list *b);

#endif
