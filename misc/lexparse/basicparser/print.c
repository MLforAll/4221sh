/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 17:30:16 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/31 22:53:49 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "bpintern.h"
#include "libft.h"
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

static void	cmdnode_putvars(t_cmdnode *ndat)
{
	char	**varsb;
	int		idx;

	if (!ndat || !(varsb = ndat->c_vars) || !*varsb)
	{
		ft_putendl("\tc_vars: NULL");
		return ;
	}
	idx = 0;
	while (*varsb)
	{
		ft_putstr("\tc_vars[");
		ft_putnbr(idx++);
		ft_putstr("]: ");
		ft_putendl(*(varsb++));
	}
}

static void	cmdnode_putredirs(t_cmdnode *ndat)
{
	t_list		*rdb;
	t_redirect	*redir;
	int			idx;

	if (!ndat || !(rdb = ndat->c_redirects))
	{
		ft_putendl("\tc_redirects: NULL");
		return ;
	}
	idx = 0;
	while (rdb)
	{
		redir = (t_redirect*)rdb->content;
		ft_putstr("\tc_redirects(");
		ft_putnbr(idx++);
		ft_putstr("): ");
		ft_putnbr(redir->io_nbr);
		ft_putstr(" \"");
		ft_putstr(g_typedesc[(int)redir->rtype]);
		ft_putstr("\" ");
		if (redir->data)
			ft_putendl(redir->data);
		else
		{
			ft_putnbr(redir->agreg);
			ft_putchar('\n');
		}
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
		cmdnode_putvars(cmddat);
		ft_putstr("\tc_path: ");
		ft_putendl((cmddat->c_path) ? cmddat->c_path : "NULL");
		cmdnode_putav(cmddat);
		cmdnode_putredirs(cmddat);
		return ;
	}
	ft_putendl(g_typedesc[(int)ndat->type]);
}
