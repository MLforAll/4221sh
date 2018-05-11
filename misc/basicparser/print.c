/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 17:30:16 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/11 23:51:03 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "../../includes/sh_parser.h"
#include "../basiclexer/g_typedesc.h"

static void	cmdnode_putav(t_cmdnode *ndat)
{
	char	**avb;
	int		idx;

	if (!ndat || !(avb = ndat->c_av) || !*avb)
	{
		ft_putendl("\tc_av: NULL");
		return ;
	}
	idx = 0;
	while (*avb)
	{
		ft_putstr("\tc_av[");
		ft_putnbr(idx++);
		ft_putstr("]: ");
		ft_putendl(*(avb++));
	}
}

static void	cmdnode_putredirs(t_cmdnode *ndat)
{
	t_list	*rdb;
	int		idx;

	if (!ndat || !(rdb = ndat->c_redirects))
	{
		ft_putendl("\tc_redirects: NULL");
		return ;
	}
	idx = 0;
	while (rdb)
	{
		ft_putstr("\tc_redirects[");
		ft_putnbr(idx++);
		ft_putstr("]: ");
		ft_putnbr(((t_redirect*)rdb->content)->io_nbr);
		ft_putstr(" \"");
		ft_putstr(g_typedesc[(int)((t_redirect*)rdb->content)->rtype]);
		ft_putstr("\" ");
		ft_putendl(((t_redirect*)rdb->content)->filename);
		rdb = rdb->next;
	}
}

void		astputelem(void *data, size_t datsize)
{
	t_astnode	*ndat;
	t_cmdnode	*cmddat;

	(void)datsize;
	ndat = (t_astnode*)data;
	if (ndat->type == 0)
	{
		cmddat = (t_cmdnode*)ndat->data;
		ft_putendl("command:");
		ft_putstr("\tc_path: ");
		ft_putendl(cmddat->c_path);
		cmdnode_putav(cmddat);
		cmdnode_putredirs(cmddat);
		return ;
	}
	ft_putendl(g_typedesc[(int)ndat->type]);
}
