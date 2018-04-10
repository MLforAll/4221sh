/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_csrkeys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 09:00:17 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/10 20:00:46 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_readline.h"

static int	rightk_action(char *buff, t_readline *rl)
{
	int				ioctl_ret;
	struct winsize	ws;

	ioctl_ret = ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	if (ioctl_ret != -1 && (rl->csr.pos + 1 + rl->prlen) % ws.ws_col == 0)
	{
		if (rl->csr.max + rl->prlen == ws.ws_col)
			return (FALSE);
		ft_putstr_fd("\n\r", STDIN_FILENO);
	}
	else
		ft_putstr_fd(buff, STDIN_FILENO);
	return (TRUE);
}

int			rl_csr_keys(char *buff, t_readline *rl)
{
	int				keys[2];

	keys[0] = (ft_strcmp(ESC_RIGHTK, buff) == 0);
	keys[1] = (ft_strcmp(ESC_LEFTK, buff) == 0);
	if (!keys[0] && !keys[1])
		return (0);
	if (keys[0] && rl->csr.pos < rl->csr.max)
	{
		if (!rightk_action(buff, rl))
			return (0);
		rl->csr.pos++;
		return (1);
	}
	if (keys[1] && rl->csr.pos > 0)
	{
		rl->csr.pos--;
		ft_putstr_fd(buff, STDIN_FILENO);
		return (1);
	}
	return (-1);
}

static void	configure_hekeys(int k[2], size_t *len, char *ckey, t_readline *rl)
{
	struct winsize	ws;

	if (!k || !len || !ckey || !rl)
		return ;
	if (k[0] && ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
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

int			rl_home_end_keys(char *buff, t_readline *rl)
{
	int				keys[2];
	size_t			len;
	char			ckey;

	keys[0] = (ft_strcmp(ESC_ENDK, buff) == 0);
	keys[1] = (ft_strcmp(ESC_HOMEK, buff) == 0);
	if (!keys[0] && !keys[1])
		return (0);
	len = 0;
	configure_hekeys(keys, &len, &ckey, rl);
	if (len == 0)
		return (-1);
	ft_putstr_fd("\033[", STDIN_FILENO);
	ft_putnbr_fd(len, STDIN_FILENO);
	ft_putchar_fd(ckey, STDIN_FILENO);
	return (1);
}
