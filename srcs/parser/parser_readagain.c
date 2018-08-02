/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_readagain.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 23:44:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/02 04:37:24 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"

static inline int	read_both(char **line,
							const char *prompt,
							t_rl_opts *ftrl_opts,
							int fd)
{
	int		status;

	if (fd == -1)
		return (ft_readline(line, prompt, ftrl_opts, NULL));
	status = get_next_line(fd, line);
	if (status == -1)
		return (FTRL_FAIL);
	if (status == 0)
		return (FTRL_EOF);
	return (FTRL_OK);
}

char				*read_till_delim(const char *prompt,
									const char *delim,
									t_uint8 opts, int fd)
{
	int			status;
	char		*ret;
	char		*line;
	t_rl_opts	ftrl_opts;

	ret = (opts & RA_BEFORE) ? ft_strdup("\n") : ft_strnew(0);
	ft_bzero(&ftrl_opts, sizeof(t_rl_opts));
	line = NULL;
	while ((status = read_both(&line, prompt, &ftrl_opts, fd)) == FTRL_OK
			|| status == FTRL_EOF)
	{
		if (status == FTRL_EOF || (ft_strequ(line, delim) && (opts & RA_WHOLE)))
			break ;
		ft_stradd(&ret, line);
		if (!delim || (delim && !(opts & RA_WHOLE) && ft_strstr(line, delim)))
			break ;
		ft_strdel(&line);
		ft_stradd(&ret, "\n");
	}
	ft_strdel(&line);
	if (status == FTRL_FAIL || status == FTRL_SIGINT)
		ft_strdel(&ret);
	return (ret);
}
