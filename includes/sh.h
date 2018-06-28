/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 01:57:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/28 21:28:09 by kdumarai         ###   ########.fr       */
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
# define SH_HISTFILE		".21sh_history"
# define SH_MAXHIST			100

# define SH_DEFAULT_PATH	"/usr/local/bin:/usr/bin:/bin:/usr/sbin"

/*
** shell types
*/

int		exec_shell(const char *path);
int		interactive_shell(void);

/*
** cmd exec
*/

void	exec_pipe(t_cmdnode *cmddat);
void	exec_pipe_clean(t_cmdnode *cmddat);
void	exec_redir(t_cmdnode *cmddat, t_tab *bakptr);
int		exec_cmd(t_cmdnode *cmddat, int async, pid_t *spid, char **env);
int		eval_line(char **line, uint8_t ragain);

/*
** autocompletion
*/

t_list	*sh_get_acres(char *line, t_cursor *csr);
char	*sh_show_acres(t_list **chs);
void	ft_aclst_rmdups(t_list **lst);

/*
** history load/save
*/

void	write_history(t_dlist *hist);
void	load_history(t_dlist **hist);

/*
** fsexp utilities
*/

char	*search_dir_for_file(const char *d_path, const char *name);
t_list	*search_files_begin(const char *f_path, const char *s_dir, int exec);

/*
** variables mgmt
*/

char	*get_env_var(char **env, const char *var);
char	*chg_env_var(char **env, const char *var, char *new);
char	*set_env_var(char ***env, const char *var, char *value);
void	del_env_var(char ***env, const char *var);

char	*set_env_from_str(char ***env, char *str);
char	*set_env_var_n(char ***env, const char *var, int value);

char	*get_lvar(const char *var);
char	*chg_lvar(const char *var, char *new);
char	*set_lvar(const char *var, char *value);
void	del_lvar(const char *var);

/*
** errors
*/

int		sh_err(int errc, const char *bltn, const char *path);
int		sh_err_ret(int errc, const char *bltn, const char *path, int retv);
int		get_errcode_for_path(const char *path, int mode, int dir);

/*
** misc functions / utilities
*/

int		ft_strchrf(char *s, char c);

int		free_return(void **data, int retv);
void	switch_traps(int ign);

void	free_tlist(void *content, size_t size);

#endif
