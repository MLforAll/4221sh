/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_readagain.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 23:44:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/08 18:53:38 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"

inline void			get_raconf(struct s_raconf *conf, \
								const char *prompt, \
								const char *delim, \
								t_uint8 opts)
{
	conf->prompt = prompt;
	conf->delim = delim;
	ft_bzero(&conf->opts, sizeof(t_rl_opts));
	conf->opts.tbell = (opts & RACONF_BELL) == RACONF_BELL;
	conf->opts.prompt_perline = (opts & RACONF_PPL) == RACONF_PPL;
	conf->opts.ac_show_result = &sh_show_acres;
	if (opts & RACONF_AC)
		conf->opts.ac_get_result = &sh_get_acres;
}

static inline int	read_both(char **line,
							struct s_raconf *conf,
							int fd)
{
	int		status;

	if (fd == -1)
		return (ft_readline(line, conf->prompt, &conf->opts, NULL));
	status = get_next_line(fd, line);
	if (status == -1)
		return (FTRL_FAIL);
	if (status == 0)
		return (FTRL_EOF);
	return (FTRL_OK);
}

char				*read_till_delim(struct s_raconf *conf,
									t_uint8 opts, int fd)
{
	int			status;
	char		*ret;
	char		*line;

	if (!(ret = (opts & RA_BEFORE) ? ft_strdup("\n") : ft_strnew(0)))
		return (NULL);
	line = NULL;
	while ((status = read_both(&line, conf, fd)) == FTRL_OK
			|| status == FTRL_EOF)
	{
		if (status == FTRL_EOF || (ft_strequ(line, conf->delim)
			&& (opts & RA_WHOLE)))
			break ;
		ft_stradd(&ret, line);
		if (!conf->delim || (conf->delim && !(opts & RA_WHOLE)
			&& ft_strstr(line, conf->delim)))
			break ;
		ft_strdel(&line);
		ft_stradd(&ret, "\n");
	}
	ft_strdel(&line);
	if (status == FTRL_FAIL || status == FTRL_SIGINT)
		ft_strdel(&ret);
	return (ret);
}
