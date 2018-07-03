/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_acshow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 01:38:20 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/03 08:32:43 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"
#include "ftrl_dev.h"
#include "ftrl_termcap.h"
#include <term.h>

/*
** draw_chs (static)   -> draw choices
**
** t_list *chs         -> linked list of choices
** unsigned int selidx -> currently selected idex
*/

static void			draw_chs(t_list *chs, unsigned int selidx)
{
	unsigned int	idx;
	char			*tgt;

	idx = 0;
	while (chs)
	{
		tgt = ((t_acres*)chs->content)->visible_str
			? ((t_acres*)chs->content)->visible_str
			: ((t_acres*)chs->content)->str;
		if (idx == selidx)
			outcap("mr");
		ft_putendl_fd(tgt, STDIN_FILENO);
		if (idx == selidx)
			outcap("me");
		chs = chs->next;
		idx++;
	}
}

/*
** clr_chs (inline static) -> clears choices (rm from screen)
**
** size_t len
*/

inline static void	clr_chs(size_t len)
{
	while (len--)
	{
		outcap("ce");
		outcap("up");
	}
	outcap("ce");
}

/*
** get_ret (static)
**
** t_list *chs      -> linked list of choices
** unsigned int idx -> currently selected idex
*/

static char			*get_ret(t_list *chs, unsigned int idx)
{
	while (idx-- && chs)
		chs = chs->next;
	return ((chs) ? ((t_acres*)chs->content)->str : NULL);
}

/*
** move_keys (static)
**
** t_cursor *csr -> cursor struct ref
** char *buff    -> read buffer
*/

static void			move_keys(t_cursor *csr, char *buff)
{
	if (ft_strequ(buff, "\033[B") && csr->pos < csr->max - 1)
		csr->pos++;
	if (ft_strequ(buff, "\033[A") && csr->pos)
		csr->pos--;
}

/*
** sh_show_acres
**
** sh_show_acres
** t_list **chs -> linked list of choices ref
*/

char				*sh_show_acres(t_list **chs)
{
	t_cursor	csr;
	ssize_t		rb;
	char		buff[5];

	csr.pos = 0;
	csr.max = ft_lstlen(*chs);
	if (csr.max > g_ws.ws_row)
		return (show_ac_result_bltn(chs));
	ft_lstmergesort(chs, &ft_acres_sortalpha, NO);
	ft_putchar_fd('\n', STDIN_FILENO);
	while (TRUE)
	{
		draw_chs(*chs, csr.pos);
		ft_bzero(&buff, sizeof(buff));
		rb = read(STDIN_FILENO, buff, 4);
		clr_chs(csr.max);
		if (rb < 1 || *buff == 4 || *buff == 3)
			break ;
		move_keys(&csr, buff);
		if (ft_strequ(buff, "\n"))
			return (get_ret(*chs, csr.pos));
	}
	return (NULL);
}
