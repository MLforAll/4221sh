/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_support.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:49:11 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/10 20:01:01 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh.h"

t_cmd	*ft_cmdnew(void)
{
	t_cmd	*ret;

	if (!(ret = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	ft_bzero(ret, sizeof(t_cmd));
	return (ret);
}

void	ft_cmdpush(t_cmd **headref, t_cmd *new)
{
	t_cmd	*tmp;

	if (!headref || !new)
		return ;
	if (!*headref)
	{
		new->prev = NULL;
		*headref = new;
		return ;
	}
	tmp = *headref;
	while (tmp->next)
		tmp = tmp->next;
	new->prev = tmp;
	tmp->next = new;
}

void	ft_cmddelone(t_cmd **cmdref)
{
	t_cmd	*curr;
	t_cmd	*next;

	if (!cmdref || !*cmdref)
		return ;
	curr = *cmdref;
	next = curr->next;
	if (curr->c_path && curr->c_path != *curr->c_argv)
		ft_strdel(&curr->c_path);
	if (curr->c_argv)
		ft_tabfree(&curr->c_argv);
	if (curr->prev)
		curr->prev->next = curr->next;
	free(curr);
	*cmdref = next;
}

void	ft_cmddel(t_cmd **headref)
{
	if (!headref || !*headref)
		return ;
	while (*headref)
	{
		ft_cmddelone(headref);
		if (*headref)
			(*headref)->prev = NULL;
	}
	*headref = NULL;
}
