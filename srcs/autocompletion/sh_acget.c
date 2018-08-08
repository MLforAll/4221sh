/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_acget.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 04:23:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/08 05:51:03 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libftreadline.h"
#include "ftrl_dev.h"
#include "sh.h"

static t_list		*get_res_with_path(char *base)
{
	char	*pathenv;
	char	**paths;
	char	**bw;
	t_list	*ret;
	t_list	*new;

	if (!base || !*base || !(pathenv = get_env_var(NULL, "PATH")))
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
	int				ret;
	unsigned long	idx;
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
	ret = 0;
	if (!(*dest = ft_strsub(line, (unsigned int)idx, csr->pos - idx)))
		return (-1);
	if (!ft_strpbrk(line, prgchk) && !ft_strpbrk(line, chkcomps)
		&& !ft_strchr(line, '/'))
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
		&& (tmp = get_env_var(NULL, "HOME"))
		&& (tmp = ft_strjoin(tmp, region + 1)))
	{
		free(region);
		region = tmp;
	}
	if (type == 1)
	{
		ret = get_res_with_path(region);
		ft_lstadd(&ret, sh_get_bltn_ac((const char*)region));
	}
	else
		ret = search_files_begin(region, NULL, FALSE);
	if (ret)
		ft_aclst_rmdups(&ret);
	free(region);
	return (ret);
}
