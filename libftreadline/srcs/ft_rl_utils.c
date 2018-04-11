/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/10 20:00:47 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include "libft.h"
#include "ft_readline.h"

int		rl_set_term(int fd, int echo, const char *prompt)
{
	struct termios	t;

	if (!prompt || tcgetattr(fd, &t))
		return (FALSE);
	if (!echo)
	{
		ft_putstr_fd(prompt, fd);
		t.c_lflag &= ~(ICANON | ECHO | ISIG);
	}
	else
		t.c_lflag |= (ICANON | ECHO | ISIG);
	tcsetattr(fd, TCSANOW, &t);
	return (TRUE);
}

void	rl_line_rm(char **line, size_t len, t_cursor *csr)
{
	char			*tmp;
	size_t			rpt;

	if (!line || len == 0 || !csr)
		return ;
	rpt = len;
	while (rpt--)
	{
		ft_putstr_fd(ESC_LEFTK, STDIN_FILENO);
		csr->pos--;
	}
	ft_putstr_fd("\033[K\033[s", STDIN_FILENO);
	if (csr->pos + len < csr->max)
		ft_putstr_fd(*line + csr->pos + len, STDIN_FILENO);
	ft_putstr_fd("\033[u", STDIN_FILENO);
	tmp = *line;
	*line = ft_strsub(tmp, 0, csr->pos);
	if (csr->pos + len < csr->max)
		ft_stradd(line, tmp + csr->pos + len);
	ft_strdel(&tmp);
	rpt = len;
	while (rpt--)
		csr->max--;
}

void	rl_line_add(char **line, char *add, t_cursor *csr)
{
	char			*tmp;
	size_t			len;

	if (!line || !add || !csr || !(len = ft_strlen(add)))
		return ;
	ft_putstr_fd("\033[K", STDIN_FILENO);
	ft_putstr_fd(add, STDIN_FILENO);
	if (csr->pos < csr->max)
	{
		ft_putstr_fd("\033[s", STDIN_FILENO);
		ft_putstr_fd(*line + csr->pos, STDIN_FILENO);
		ft_putstr_fd("\033[u", STDIN_FILENO);
	}
	tmp = *line;
	*line = ft_strsub(tmp, 0, csr->pos);
	ft_stradd(line, add);
	if (csr->pos < csr->max)
		ft_stradd(line, tmp + csr->pos);
	ft_strdel(&tmp);
	csr->max += len;
	csr->pos += len;
}

int		rl_input_add_text(char *buff, char **line, t_cursor *csr)
{
	char			add[5];
	unsigned int	idx;

	if (*buff == 27)
		return (0);
	idx = 0;
	ft_bzero(add, sizeof(add));
	while (*buff)
	{
		if (ft_isprint(*buff))
		{
			add[idx] = *buff;
			idx++;
		}
		buff++;
	}
	rl_line_add(line, add, csr);
	return ((idx > 0));
}

int		rl_input_rm_text(char **line, char *buff, t_cursor *csr)
{
	int				keys[2];

	keys[0] = (*buff == 127);
	keys[1] = (ft_strcmp(buff, ESC_DELK) == 0);
	if (!keys[0] && !keys[1])
		return (0);
	if (keys[0] && csr->pos > 0)
	{
		rl_line_rm(line, 1, csr);
		return (1);
	}
	else if (keys[1] && csr->pos < csr->max)
	{
		ft_putstr_fd(ESC_RIGHTK, STDIN_FILENO);
		csr->pos++;
		rl_line_rm(line, 1, csr);
		return (1);
	}
	return (-1);
}
