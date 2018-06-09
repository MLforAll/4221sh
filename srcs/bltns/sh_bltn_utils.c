/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_bltn_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 22:23:23 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/09 23:47:45 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh.h"

static int	get_opt_code(char c, const char *charset)
{
	unsigned int	idx;

	idx = 0;
	while (charset[idx])
	{
		if ((char)charset[idx] == c)
			return (1 << idx);
		++idx;
	}
	return (-c);
}

static int	chk_arg(char *arg, const char *charset)
{
	int				ret;
	int				new;
	unsigned int	sidx;
	char			*tmp;

	if (!arg[1] && (tmp = ft_strchr(charset, '\004')))
		return (1 << (tmp - charset));
	ret = 0;
	sidx = 1;
	while (arg[sidx])
	{
		if ((new = get_opt_code(arg[sidx++], charset)) < 0)
			return (new);
		ret |= new;
	}
	return (ret);
}

int			get_bltn_opts(int ac, char **av, int *idx, const char *charset)
{
	int		ret;
	int		new;
	int		bltn_idx;
	int		*iptr;

	if (ac == 1 || !charset)
		return (0);
	ret = 0;
	bltn_idx = 1;
	iptr = (idx) ? idx : &bltn_idx;
	while (av[*iptr])
	{
		if (av[*iptr][0] == '-')
		{
			if ((new = chk_arg(av[*iptr], charset)) < 0)
				return (new);
			ret |= new;
			(*iptr)++;
		}
		else
			break ;
	}
	return (ret);
}
