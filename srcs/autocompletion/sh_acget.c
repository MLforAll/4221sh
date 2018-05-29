/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_acget.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 04:23:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/28 23:34:10 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libftreadline.h"
#include "sh.h"

static t_list		*get_res_with_path(char *base)
{
	char	*pathenv;
	char	**paths;
	char	**bw;
	t_list	*ret;
	t_list	*new;

	if (!base || !*base || !(pathenv = getenv("PATH")))
		return (NULL);
	paths = ft_strsplit(pathenv, ':');
	bw = paths;
	ret = NULL;
	while (*bw)
	{
		if ((new = search_files_begin(base, *bw, TRUE)))
			ft_lstadd(&ret, new);
		bw++;
	}
	ft_tabfree(&paths);
	return (ret);
}

inline static int	get_region(char **dest, char *line, t_cursor *csr)
{
	unsigned int	idx;
	int				ret;
	const char		*chkcomps = " ><&=";
	const char		*prgchk = "|;";

	if (!dest || !line || !csr)
		return (-1);
	idx = csr->pos;
	while (idx--)
	{
		if ((ret = (ft_strchr(prgchk, line[idx]) != NULL))
			|| ft_strchr(chkcomps, line[idx]))
			break ;
	}
	idx++;
	if (!(*dest = ft_strsub(line, idx, csr->pos - idx)))
		return (-1);
	if (!ft_strpbrk(line, prgchk) && !ft_strpbrk(line, chkcomps))
		ret = 1;
	return (ret);
}

t_list				*sh_get_acres(char *line, t_cursor *csr)
{
	t_list	*ret;
	char	*region;
	char	*tmp;
	int		type;

	if ((type = get_region(&region, line, csr)) == -1)
		return (NULL);
	if (*region == '~'
		&& (tmp = getenv("HOME"))
		&& (tmp = ft_strjoin(tmp, region + 1)))
	{
		free(region);
		region = tmp;
	}
	if (type == 1)
		ret = get_res_with_path(region);
	else
		ret = search_files_begin(region, NULL, FALSE);
	free(region);
	return (ret);
}
