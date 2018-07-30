/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_loadsave.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 01:18:21 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/30 03:11:16 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "sh.h"

static int	open_hist_file(int o_mode, int o_perms)
{
	char	*homeenv;
	char	*fpath;
	int		fd;

	fpath = NULL;
	if (!(homeenv = getenv("HOME"))
		|| !(fpath = get_elem_path(homeenv, SH_HISTFILE))
		|| (fd = open(fpath, o_mode, o_perms)) == -1)
	{
		ft_strdel(&fpath);
		return (-1);
	}
	free(fpath);
	return (fd);
}

static char	*get_hist_string(t_dlist *hist)
{
	char	*line;
	char	*histbuff;

	histbuff = NULL;
	while (hist->next)
		hist = hist->next;
	while (hist->prev)
	{
		if (hist->content
			&& (!(line = ft_strnew_replace((char*)hist->content, "\n", "\032"))
				|| !ft_stradd(&histbuff, line)
				|| !ft_stradd(&histbuff, "\n")))
		{
			free(line);
			free(histbuff);
			return (NULL);
		}
		free(line);
		hist = hist->prev;
	}
	return (histbuff);
}

void		write_history(t_dlist *hist)
{
	char	*histbuff;
	int		fd;

	if (!hist || !(histbuff = get_hist_string(hist)))
		return ;
	if ((fd = open_hist_file(O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
	{
		free(histbuff);
		return ;
	}
	ft_putstr_fd(histbuff, fd);
	free(histbuff);
	(void)close(fd);
}

void		load_history(t_dlist **hist)
{
	char			*buff;
	char			*line;
	int				fd;
	unsigned int	limit;

	*hist = NULL;
	if ((fd = open_hist_file(O_RDONLY, 0)) == -1)
		return ;
	buff = NULL;
	limit = SH_MAXHIST;
	while (get_next_line(fd, &buff) > 0)
	{
		if (!(line = ft_strnew_replace(buff, "\032", "\n")))
		{
			ft_dlstdel(hist, &ftrl_histdelf);
			return ;
		}
		if (limit == 0)
			ftrl_histdellast(hist);
		ftrl_histadd(hist, line);
		free(line);
		ft_strdel(&buff);
		limit -= (limit > 0);
	}
	(void)close(fd);
}
