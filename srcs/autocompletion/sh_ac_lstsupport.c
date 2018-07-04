/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ac_lstsupport.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 21:55:07 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/04 01:59:21 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ftrl_dev.h"

static void	free_aclst(void *content, size_t size)
{
	t_acres	*dat;

	if (size == 0)
		return ;
	dat = (t_acres*)content;
	free(dat->str);
	free(dat->visible_str);
	free(content);
}

static void	ft_aclst_rmdups_check(t_list **lst, t_list *bw, t_list *prev)
{
	t_list	**ptr;
	t_list	*chk;

	chk = *lst;
	while (chk && bw && bw->content && chk != bw)
	{
		if (ft_strequ(((t_acres*)bw->content)->str,
			((t_acres*)chk->content)->str))
		{
			ptr = (!prev) ? lst : &prev->next;
			*ptr = bw->next;
			ft_lstdelone(&bw, &free_aclst);
			bw = prev;
		}
		else
			chk = chk->next;
	}
}

void		ft_aclst_rmdups(t_list **lst)
{
	t_list	*bw;
	t_list	*prev;

	bw = (lst) ? *lst : NULL;
	prev = NULL;
	while (bw)
	{
		ft_aclst_rmdups_check(lst, bw, prev);
		prev = bw;
		bw = bw->next;
	}
}
