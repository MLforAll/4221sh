/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_loadsave.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 01:18:21 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/21 17:02:07 by kdumarai         ###   ########.fr       */
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

void		write_history(t_dlist *hist)
{
	char	*histbuff;
	int		fd;

	if (!(histbuff = ft_strnew(0)))
		return ;
	while (hist->next)
		hist = hist->next;
	while (hist->prev)
	{
		if (hist->content && (!ft_stradd(&histbuff, (char*)hist->content)
			|| !ft_stradd(&histbuff, "\n")))
		{
			free(histbuff);
			return ;
		}
		hist = hist->prev;
	}
	if ((fd = open_hist_file(O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
	{
		free(histbuff);
		return ;
	}
	ft_putstr_fd(histbuff, fd);
	close(fd);
}

void		load_history(t_dlist **hist)
{
	char			*buff;
	int				fd;
	unsigned int	limit;

	*hist = NULL;
	if ((fd = open_hist_file(O_RDONLY, 0)) == -1)
		return ;
	buff = NULL;
	limit = SH_MAXHIST;
	while (get_next_line(fd, &buff) > 0)
	{
		if (limit == 0)
			ftrl_histdellast(hist);
		ftrl_histadd(hist, buff);
		ft_strdel(&buff);
		limit -= (limit > 0);
	}
	close(fd);
}
