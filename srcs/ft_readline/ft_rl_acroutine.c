/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_acroutine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:12:06 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/10 20:00:53 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include "ft_readline.h"
#include "sh.h"

static char		*get_highest_common(t_list *lst)
{
	int				first;
	size_t			len;
	size_t			new;

	if (!lst)
		return (NULL);
	first = TRUE;
	len = 0;
	while (lst->next)
	{
		new = 0;
		new = ft_strcmpi(lst->content, lst->next->content);
		len = (new < len || first) ? new : len;
		if (first)
			first = FALSE;
		lst = lst->next;
	}
	return (len == 0 ? NULL : ft_strsub(lst->content, 0, len));
}

static void		show_choices(t_list **res, const char *prompt, char *line)
{
	ft_putchar_fd('\n', STDIN_FILENO);
	ft_lstmergesort(res, &ft_lstsortalpha, NO);
	ft_putlst_fd(*res, STDIN_FILENO);
	ft_putstr_fd(prompt, STDIN_FILENO);
	ft_putstr_fd(line, STDIN_FILENO);
}

static char		*get_region(char *line, t_cursor *csr)
{
	char			*tmp;
	unsigned int	idx;

	if (csr->pos == csr->max)
	{
		if (!(tmp = get_last_component(line, ' ')))
			return (NULL);
		return ((tmp) ? ft_strdup(tmp) : NULL);
	}
	idx = csr->pos;
	while (idx--)
	{
		if (line[idx] == ' ')
			break ;
	}
	idx++;
	return (ft_strsub(line, idx, csr->pos - idx));
}

void			ac_line(char **line, t_cursor *csr, const char *pr, char **env)
{
	char			*region;
	t_list			*res;
	char			*fname;
	char			*diff;
	char			*base;

	if (!(region = get_region(*line, csr)))
		return ;
	fname = get_name_from_path(region);
	res = get_ac_result(*line, region, env);
	base = (res && !res->next) ? res->content : get_highest_common(res);
	if (base && (diff = ft_strdiff(base, fname)) && *diff)
		rl_line_add(line, diff, csr);
	else if (res && res->next)
		show_choices(&res, pr, *line);
	if ((res && res->next) || !res)
		ft_putchar_fd('\a', STDIN_FILENO);
	if (res && base && base == res->content && res->content_size != DT_LNK)
		rl_line_add(line, (res->content_size == DT_DIR) ? "/" : " ", csr);
	if (base && base != res->content)
		ft_strdel(&base);
	ft_strdel(&region);
	ft_lstdel(&res, &free_tlist);
}
