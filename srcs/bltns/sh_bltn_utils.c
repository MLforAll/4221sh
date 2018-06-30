/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_bltn_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 22:23:23 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/30 16:16:00 by kdumarai         ###   ########.fr       */
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
			return ((int)(1 << idx));
		++idx;
	}
	return ((int)-c);
}

static void	do_overrides(char arg_char, int *ret,
						const char *charset, const char *overrides)
{
	const char		*chr;
	const char		*tmp;
	int				code;

	if (!(chr = ft_strchr(overrides, arg_char)))
		return ;
	tmp = chr - (chr != overrides);
	while (tmp != overrides && *tmp != '|')
		tmp--;
	while (*tmp && *tmp != '|')
	{
		if (*tmp != *chr)
		{
			code = get_opt_code(*tmp, charset);
			if (code >= 0 && (*ret & code) == code)
				*ret ^= code;
		}
		tmp++;
	}
}

static int	chk_arg(char *arg, int *ret,
					const char *charset, const char *overrides)
{
	int				new;
	unsigned int	sidx;
	const char		*tmp;

	if (!arg[1] && (tmp = ft_strchr(charset, '\004')))
	{
		*ret = (int)(1 << (tmp - charset));
		return (0);
	}
	sidx = 1;
	while (arg[sidx])
	{
		if ((new = get_opt_code(arg[sidx], charset)) < 0)
			return (new);
		if (overrides)
			do_overrides(arg[sidx], ret, charset, overrides);
		*ret |= new;
		sidx++;
	}
	return (0);
}

int			get_bltn_opts(char **av, int *idx, const char *charset,
							const char *overrides)
{
	int		ret;
	int		err;
	int		bltn_idx;
	int		*iptr;

	bltn_idx = 1;
	iptr = (idx) ? idx : &bltn_idx;
	if (!av[*iptr] || !charset)
		return (0);
	ret = 0;
	while (av[*iptr])
	{
		if (av[*iptr][0] == '-')
		{
			if (av[*iptr][1] != '-'
				&& (err = chk_arg(av[*iptr], &ret, charset, overrides)) < 0)
				return (err);
			(*iptr)++;
		}
		else
			break ;
	}
	return (ret);
}
