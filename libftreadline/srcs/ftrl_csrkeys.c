/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_csrkeys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 09:00:17 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/13 06:55:19 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ftrl_internal.h"

static int	rightk_action(t_readline *rl)
{
	int				ioctl_ret;
	struct winsize	ws;

	ioctl_ret = ioctl(rl->opts->outfd, TIOCGWINSZ, &ws);
	if (ioctl_ret != -1 && (rl->csr.pos + 1 + rl->prlen) % ws.ws_col == 0)
	{
		if (rl->csr.max + rl->prlen == ws.ws_col)
			return (FALSE);
		ft_putstr_fd("\n\r", rl->opts->outfd);
	}
	else
		ft_putstr_fd(rl->movs.rightm, rl->opts->outfd);
	return (TRUE);
}

t_keyact	rl_csr_keys(char *buff, t_readline *rl)
{
	int				keys[2];

	keys[0] = (ft_strequ(rl->keys.rightk, buff));
	keys[1] = (ft_strequ(rl->keys.leftk, buff));
	if (!keys[0] && !keys[1])
		return (kKeyNone);
	if (keys[0] && rl->csr.pos < rl->csr.max)
	{
		if (!rightk_action(rl))
			return (kKeyNone);
		rl->csr.pos++;
		return (1);
	}
	if (keys[1] && rl->csr.pos > 0)
	{
		rl->csr.pos--;
		ft_putstr_fd(rl->movs.leftm, rl->opts->outfd);
		return (kKeyOK);
	}
	return (kKeyFail);
}

static void	configure_hekeys(int k[2], size_t *len, char *ckey, t_readline *rl)
{
	struct winsize	ws;

	if (!k || !len || !ckey || !rl)
		return ;
	if (k[0] && ioctl(rl->opts->outfd, TIOCGWINSZ, &ws) == -1)
		return ;
	if (k[0] && rl->csr.pos < rl->csr.max
		&& rl->csr.max + rl->prlen < ws.ws_col)
	{
		*len = rl->csr.max - rl->csr.pos;
		*ckey = 'C';
		rl->csr.pos = rl->csr.max;
	}
	else if (k[1] && rl->csr.pos > 0)
	{
		*len = rl->csr.pos;
		*ckey = 'D';
		rl->csr.pos = 0;
	}
}

t_keyact	rl_home_end_keys(char *buff, t_readline *rl)
{
	int				keys[2];
	size_t			len;
	char			ckey;

	keys[0] = (ft_strequ(rl->keys.endk, buff));
	keys[1] = (ft_strequ(rl->keys.homek, buff));
	if (!keys[0] && !keys[1])
		return (kKeyNone);
	len = 0;
	configure_hekeys(keys, &len, &ckey, rl);
	if (len == 0)
		return (kKeyFail);
	ft_putstr_fd("\033[", rl->opts->outfd);
	ft_putnbr_fd(len, rl->opts->outfd);
	ft_putchar_fd(ckey, rl->opts->outfd);
	return (kKeyOK);
}
