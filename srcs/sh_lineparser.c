/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lineparser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 02:37:36 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/10 20:00:37 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh.h"

static int	is_c_charset(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (TRUE);
		charset++;
	}
	return (FALSE);
}

static void	add_elem(t_list **dest, char **last, unsigned int *idx)
{
	t_list			*new;

	if (!dest || !last || !idx)
		return ;
	if (*idx > 0)
	{
		if (!(new = ft_lstnew(NULL, 0)))
			return ;
		if ((new->content = ft_strsub(*last, 0, *idx)))
			new->content_size = *idx + 1;
		ft_lstpush(dest, new);
	}
	*last = (*last) + *idx + 1;
	*idx = 0;
}

int			ft_splitquote(t_list **dest, char *s, char *charset, char *cs)
{
	char			*last;
	unsigned int	idx;
	int				split;

	(dest) ? *dest = NULL : 0;
	if (!dest || !charset || !(last = s))
		return (FALSE);
	idx = 0;
	split = TRUE;
	while (last[idx])
	{
		if (is_c_charset(last[idx], cs) && (idx == 0 || last[idx - 1] != '\\'))
			split = !split;
		if (!last[idx] || (is_c_charset(last[idx], charset) && split))
			add_elem(dest, &last, &idx);
		else
			idx++;
	}
	if (!split)
	{
		ft_lstdel(dest, &free_tlist);
		return (FALSE);
	}
	add_elem(dest, &last, &idx);
	return (TRUE);
}

char		*ft_strrmquote(char *s, char *cset)
{
	char			*ret;
	char			*tmp;
	unsigned int	idx;

	if (!s || !(ret = ft_strnew(ft_strlen(s))))
		return (NULL);
	idx = 0;
	tmp = s;
	while (*tmp)
	{
		if (*tmp == '\\' && is_c_charset(tmp[1], cset))
			tmp++;
		if (!is_c_charset(*tmp, cset) || (tmp > s && *(tmp - 1) == '\\'))
			ret[idx++] = *tmp;
		tmp++;
	}
	tmp = ret;
	ret = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (ret);
}
