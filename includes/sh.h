/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 01:57:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/06 19:46:53 by kdumarai         ###   ########.fr       */
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
# include "sh_jobs.h"

/*
** macros
*/

# define SH_GEN_NAME		"21sh"
# define SH_RC				".21shrc"
# define SH_HISTFILE		".21sh_history"
# define SH_MAXHIST			500

# define SH_DEFAULT_PATH	"/usr/local/bin:/usr/bin:/bin:/usr/sbin"

/*
** globals
** -------
**
** Note: extern declaration before to conform with -Weverything
*/

extern char	*g_sh_name;
char		*g_sh_name;

/*
** shell types
*/

t_uint8		shell_init(char **av);
int			exec_shell(const char *path);
int			interactive_shell(void);

/*
** cmd exec
*/

void		exec_pipe(t_cmdnode *cmddat);
int			exec_redir(t_cmdnode *cmddat, t_tab *bakptr);
int			exec_cmd(t_cmdnode *cmddat, t_uint8 async, pid_t *spid, char **env);

/*
** line eval
*/

t_cmdnode	*eval_ast(t_btree *node, t_tab *pids);
t_cmdnode	*eval_pipe(t_btree *node, t_tab *pids);
t_cmdnode	*eval_semi(t_btree *node, t_tab *pids);
t_cmdnode	*eval_andif(t_btree *node, t_tab *pids);
t_cmdnode	*eval_orif(t_btree *node, t_tab *pids);
t_cmdnode	*eval_background(t_btree *node, t_tab *pids);

int			eval_line(char **line, int fd);

/*
** autocompletion
*/

t_list		*sh_get_acres(char *line, t_cursor *csr);
char		*sh_show_acres(t_list **chs);

/*
** history load/save
*/

void		write_history(t_dlist *hist);
void		load_history(t_dlist **hist);

/*
** variables mgmt
** --------------
**
** env functions integrate with libc's functions like getenv()
** local vars function contain ``lvar'' in their name.
*/

char		*get_env_var(char **env, const char *var);
char		*chg_env_var(char **env, const char *var, char *new);
char		*set_env_var(char ***env, const char *var, char *value);
void		del_env_var(char ***env, const char *var);

char		*set_env_from_str(char ***env, char *str);
char		*set_env_var_n(char ***env, const char *var, int value);

char		*get_lvar(const char *var);
char		*chg_lvar(const char *var, char *new);
char		*set_lvar(const char *var, char *value);
char		*set_lvar_n(const char *var, int value);
void		del_lvar(const char *var);

/*
** errors
*/

void		sh_err(t_errs errc, const char *bltn, const char *path);
int			sh_err_ret(t_errs errc,
						const char *bltn,
						const char *path,
						int rvl);

t_errs		get_errcode_for_path(const char *path, int mode,
								t_uint8 dir, t_uint8 creatable);

/*
** fsexp utilities
*/

char		*search_dir_for_file(const char *d_path, const char *name);
t_list		*search_files_begin(const char *f_path,
								const char *s_dir, int exec);

/*
** signals
*/

void		switch_traps(int ign);

#endif
