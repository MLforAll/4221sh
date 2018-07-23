/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 01:57:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/23 22:16:33 by kdumarai         ###   ########.fr       */
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

# define SH_GEN_NAME		"21sh"
# define SH_RC				".21shrc"
# define SH_HISTFILE		".21sh_history"
# define SH_MAXHIST			100

# define SH_DEFAULT_PATH	"/usr/local/bin:/usr/bin:/bin:/usr/sbin"

/*
** globals
*/

extern const char	*g_sh_name;
const char			*g_sh_name;

/*
** shell types
*/

int			exec_shell(const char *path);
int			interactive_shell(void);

/*
** cmd exec
*/

void		exec_pipe(t_cmdnode *cmddat);
void		exec_pipe_clean(t_cmdnode *cmddat);
void		exec_redir(t_cmdnode *cmddat, t_tab *bakptr);
int			exec_cmd(t_cmdnode *cmddat, int async, pid_t *spid, char **env);

/*
** line eval
*/

t_cmdnode	*eval_pipe(t_cmdnode *a, t_cmdnode *b, t_tab *pids);
t_cmdnode	*eval_semi(t_cmdnode *a, t_cmdnode *b);
t_cmdnode	*eval_andif(t_cmdnode *a, t_cmdnode *b);
t_cmdnode	*eval_orif(t_cmdnode *a, t_cmdnode *b);
t_cmdnode	*eval_background(t_cmdnode *a, t_cmdnode *b);

int			eval_line(char **line, t_uint8 ragain);

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
						const char *bltn, const char *path, int rvl);
int			get_errcode_for_path(const char *path, int mode, int dir);

/*
** fsexp utilities
*/

char		*search_dir_for_file(const char *d_path, const char *name);
t_list		*search_files_begin(const char *f_path,
								const char *s_dir, int exec);

/*
** misc functions / utilities
*/

int			ft_strchrf(const char *s, char c);
int			free_return(void **data, int retv);

void		switch_traps(int ign);

#endif
