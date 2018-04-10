/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tlist_support.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 21:55:07 by kdumarai          #+#    #+#             */
/*   Updated: 2018/02/23 14:28:43 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	free_tlist(void *content, size_t size)
{
	(void)size;
	free(content);
}

void	ft_lstrmdups(t_list **lst)
{
	t_list	*bw;
	t_list	*prev;
	t_list	*chk;
	t_list	**ptr;

	bw = (lst) ? *lst : NULL;
	prev = NULL;
	while (bw)
	{
		chk = *lst;
		while (chk && bw && bw->content && chk != bw)
		{
			if (chk->content && ft_strcmp(bw->content, chk->content) == 0)
			{
				ptr = (!prev) ? lst : &prev->next;
				*ptr = bw->next;
				ft_lstdelone(&bw, &free_tlist);
				bw = prev;
			}
			else
				chk = chk->next;
		}
		prev = bw;
		bw = bw->next;
	}
}

int		ft_lstsortalpha(t_list *a, t_list *b)
{
	int		diff;

	if (!a || !b || !a->content || !b->content)
		return (0);
	diff = ft_strcmp(a->content, b->content);
	return ((diff > 0));
}
