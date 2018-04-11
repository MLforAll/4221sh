/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:46:30 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/10 20:00:45 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include "libft.h"
# include <sys/ioctl.h>

/*
** ESC Sequences Codes
*/

# define ESC_LEFTK	"\033[D"
# define ESC_RIGHTK	"\033[C"
# define ESC_HOMEK	"\033[H"
# define ESC_ENDK	"\033[F"
# define ESC_DELK	"\033[3~"
# define ESC_CLRL	"\033[K"
# define ESC_SAVEP	"\033[s"
# define ESC_RESTP	"\033[u"

/*
** struct for cursor mgmt
*/

typedef struct	s_cursor
{
	unsigned int	pos;
	size_t			max;
}				t_cursor;

/*
** linked list for history mgmt
*/

typedef struct	s_history
{
	char				*line;
	struct s_history	*next;
	struct s_history	*prev;
}				t_history;

/*
** struct for moving around data
*/

typedef struct	s_readline
{
	const char	*prompt;
	size_t		prlen;
	t_cursor	csr;
	t_history	*hist;
}				t_readline;

/*
** Functions
*/

char			*ft_readline(const char *prompt, char **env, t_history *hist);

/*
** Utilities functions
*/

int				rl_csr_keys(char *buff, t_readline *rl);
int				rl_home_end_keys(char *buff, t_readline *rl);

void			rl_line_rm(char **line, size_t len, t_cursor *csr);
void			rl_line_add(char **line, char *add, t_cursor *csr);
int				rl_set_term(int fd, int echo, const char *prompt);
int				rl_input_add_text(char *buff, char **line, t_cursor *csr);
int				rl_input_rm_text(char **line, char *buff, t_cursor *csr);

/*
** Autocompletion
*/

void			ac_line(char **line, t_cursor *csr, const char *pr, char **env);
t_list			*get_ac_result(char *line, char *region, char **env);

/*
** History
*/

t_history		*ft_histnew(char *line);
void			ft_histadd(t_history **headref, char *line);
void			ft_histdelone(t_history	**hist);
void			ft_histdel(t_history **headref);
int				rl_history_keys(t_history **history, char *buff, char **line);

#endif
