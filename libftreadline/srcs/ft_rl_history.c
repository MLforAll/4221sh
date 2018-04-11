/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 07:11:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/10 20:00:54 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_readline.h"

t_history	*ft_histnew(char *line)
{
	t_history	*ret;

	if (!(ret = (t_history*)malloc(sizeof(t_history))))
		return (NULL);
	ft_bzero(ret, sizeof(t_history));
	if (!(ret->line = ft_strdup(line)))
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

void		ft_histadd(t_history **headref, char *line)
{
	t_history	*new;

	if (!headref || !line || !(new = ft_histnew(line)))
		return ;
	if (*headref)
	{
		ft_histdelone(headref);
		(*headref)->prev = new;
		new->next = *headref;
	}
	*headref = ft_histnew("");
	new->prev = *headref;
	(*headref)->next = new;
}

void		ft_histdelone(t_history **hist)
{
	t_history	*bak;

	if (!hist || !*hist)
		return ;
	bak = (*hist)->next;
	if ((*hist)->prev)
		(*hist)->prev->next = (*hist)->next;
	free((*hist)->line);
	free(*hist);
	*hist = bak;
}

void		ft_histdel(t_history **headref)
{
	if (!headref)
		return ;
	while (*headref)
	{
		ft_histdelone(headref);
		if (*headref)
			(*headref)->prev = NULL;
	}
	*headref = NULL;
}

int			rl_history_keys(t_history **history, char *buff, char **line)
{
	int		ret;
	int		keys[2];

	keys[0] = (buff && ft_strcmp("\033[A", buff) == 0);
	keys[1] = (buff && ft_strcmp("\033[B", buff) == 0);
	if (!line || !history || (!keys[0] && !keys[1]))
		return (0);
	if (!*history)
		return (-1);
	ret = -1;
	if (keys[0] && (*history)->next)
	{
		*history = (*history)->next;
		ret = 1;
	}
	if (keys[1] && (*history)->prev)
	{
		*history = (*history)->prev;
		ret = 1;
	}
	if (ret == -1)
		return (-1);
	ft_strdel(line);
	*line = ft_strdup((*history)->line);
	return (1);
}
