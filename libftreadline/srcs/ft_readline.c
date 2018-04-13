/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/13 06:45:08 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"

static void		act_keys(char **line, char *buff, t_readline *rl)
{
	int				rval;
	unsigned int	idx;
	static t_keyact	(*f[3])(char*, t_readline*) =
	{&rl_csr_keys, &rl_home_end_keys, NULL};

	if (!line || !*line || !buff)
		return ;
	if ((rval = rl_history_keys(&rl->opts->hist, buff, line)) > 0 && *line)
	{
		ft_putstr_fd("\r\033[K", STDIN_FILENO);
		ft_putstr_fd(rl->prompt, STDIN_FILENO);
		ft_putstr_fd(*line, STDIN_FILENO);
		rl->csr.max = ft_strlen(*line);
		rl->csr.pos = rl->csr.max;
	}
	idx = -1;
	while (f[++idx])
	{
		if ((rval = f[idx](buff, rl)) > 0)
			return ;
	}
}

static void		act_on_buff(char *buff, char **line, t_readline *rl)
{
	int				retval;

	if (!line || !*line || !buff)
		return ;
	if (rl_input_add_text(buff, line, &rl->csr))
		return ;
	if ((retval = rl_input_rm_text(line, buff, &rl->csr)) == 1)
		return ;
	if (*buff == 4 || *buff == 3 || *buff == 21)
		ft_strdel(line);
	if (*buff == 3 || *buff == 21)
		*line = ft_strnew(0);
	if (*buff == 21)
	{
		ft_putstr_fd("\r\033[K", STDIN_FILENO);
		ft_putstr_fd(rl->prompt, STDIN_FILENO);
		ft_bzero(&rl->csr, sizeof(t_cursor));
		return ;
	}
	if (*buff == 4 || *buff == 3)
		return ;
}

static void		print_end_newlines(char *line, char *buff, t_readline *rl)
{
	struct winsize	ws;
	size_t			times;
	size_t			linelen;
	char			*nlb;

	if (!line || !rl || rl->csr.pos == rl->csr.max)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		return ;
	}
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
		return ;
	linelen = ft_strlen(line) + rl->prlen;
	times = linelen / ws.ws_col + (linelen % ws.ws_col != 0);
	times -= rl->csr.pos / ws.ws_col;
	times = (times <= 0) ? 1 : times;
	times += (buff && *buff != '\n');
	if (!(nlb = (char*)malloc(sizeof(char) * (times + 1))))
		return ;
	ft_memset(nlb, '\n', times);
	nlb[times] = '\0';
	ft_putstr_fd(nlb, STDIN_FILENO);
	free(nlb);
}

char			*ft_readline(const char *prompt, t_rl_opts *opts)
{
	char			buff[5];
	t_readline		rl;
	char			*ret;

	if (!rl_init(&rl, prompt, opts) || !rl_set_term(opts->outfd, NO, prompt))
		return (NULL);
	ft_bzero(buff, sizeof(buff));
	ret = ft_strnew(0);
	while (ret && read(opts->outfd, buff, 4) > 0)
	{
		act_keys(&ret, buff, &rl);
		act_on_buff(buff, &ret, &rl);
		//if (*buff == '\t')
		//	rl_ac_routine(&ret, &rl);
		if (*buff == '\n' || *buff == 4 || *buff == 3)
			break ;
		ft_bzero(buff, sizeof(buff));
	}
	print_end_newlines(ret, buff, &rl);
	rl_set_term(opts->outfd, YES, prompt);
	return (ret);
}
