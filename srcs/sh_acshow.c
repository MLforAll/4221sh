/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_acshow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 01:38:20 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/28 02:23:42 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"
#include <term.h>

static void	draw_chs(t_list *chs, unsigned int selidx)
{
	unsigned int	idx;

	idx = 0;
	while (chs)
	{
		if (idx == selidx)
			ft_putstr("--> ");
		ft_putstr_fd(((t_acres*)chs->content)->visible_str, STDIN_FILENO);
		ft_putstr_fd("\r\n", STDIN_FILENO);
		chs = chs->next;
		idx++;
	}
}

static int	putcf(int c)
{
	return (write(STDIN_FILENO, (void*)&c, 1));
}

static void	clr_chs(size_t len)
{
	while (len--)
	{
		tputs(tgetstr("ce", NULL), 1, &putcf);
		tputs(tgetstr("up", NULL), 1, &putcf);
	}
	tputs(tgetstr("ce", NULL), 1, &putcf);
}

static char	*get_ret(t_list *chs, unsigned int idx)
{
	while (idx-- && chs)
		chs = chs->next;
	return ((chs) ? ((t_acres*)chs->content)->str : NULL);
}

char		*sh_show_acres(t_list **chs)
{
	t_cursor	csr;
	char		buff[5];

	tputs(tgetstr("ke", NULL), 1, &putcf);
	ft_lstmergesort(chs, &ft_acres_sortalpha, NO);
	csr.pos = 0;
	csr.max = ft_lstlen(*chs);
	ft_putstr_fd("\r\n", STDIN_FILENO);
	if (csr.max > 10)
	{
		ft_putstr_fd("Can't show them all!\r\n", STDIN_FILENO);
		return (NULL);
	}
	draw_chs(*chs, csr.pos);
	ft_bzero(&buff, sizeof(buff));
	while (read(STDIN_FILENO, buff, 4) > 0)
	{
		if (ft_strequ(buff, "\033[B") && csr.pos < csr.max)
			csr.pos++;
		if (ft_strequ(buff, "\033[A") && csr.pos)
			csr.pos--;
		clr_chs(csr.max);
		if (ft_strequ(buff, "\n"))
		{
			tputs(tgetstr("ks", NULL), 1, &putcf);
			return (get_ret(*chs, csr.pos));
		}
		draw_chs(*chs, csr.pos);
		ft_bzero(&buff, sizeof(buff));
	}
	tputs(tgetstr("ks", NULL), 1, &putcf);
	return (NULL);
}
