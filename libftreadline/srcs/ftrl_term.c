/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 02:01:46 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/13 06:54:56 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include "ftrl_internal.h"

int		rl_set_term(int fd, int echo, const char *prompt)
{
	struct termios	t;

	if (tcgetattr(fd, &t))
		return (FALSE);
	if (!echo)
	{
		if (prompt)
			ft_putstr_fd(prompt, fd);
		t.c_lflag &= ~(ICANON | ECHO | ISIG);
		outcap("ks");
	}
	else
	{
		t.c_lflag |= (ICANON | ECHO | ISIG);
		outcap("ke");
	}
	tcsetattr(fd, TCSANOW, &t);
	return (TRUE);
}

inline static void set_keys_movs(t_keys *keys, t_mov *movs)
{
	keys->leftk = tgetstr("kl", NULL);
	keys->rightk = tgetstr("kr", NULL);
	keys->upk = tgetstr("ku", NULL);
	keys->downk = tgetstr("kd", NULL);
	keys->homek = tgetstr("kh", NULL);
	keys->endk = tgetstr("kH", NULL);
	keys->clrk = tgetstr("kE", NULL);
	movs->leftm = tgetstr("le", NULL);
	movs->rightm = tgetstr("nd", NULL);
}

static int			putcf(int c)
{
	static int	outfd = -1;

	if (outfd == -1)
	{
		outfd = c;
		return (0);
	}
	write(outfd, &c, 1);
	return (1);
}

int		outcap(char *name)
{
	char	*cap;

	cap = tgetstr(name, NULL);
	if (!cap)
		return (FALSE);
	tputs(cap, 1, &putcf);
	return (TRUE);
}

int		rl_init(t_readline *rl, const char *prompt, t_rl_opts *opts)
{
	char	*termenv;
	int		dumbmode;

	ft_bzero(rl, sizeof(t_readline));
	rl->prompt = prompt;
	rl->prlen = ft_strlen_nocolor(prompt);
	rl->opts = opts;
	dumbmode = FALSE;
	if (!(termenv = getenv("TERM")))
	{
		termenv = "dumb";
		dumbmode = TRUE;
	}
	if (!(tgetent(NULL, termenv)))
		return (FALSE);
	putcf(opts->outfd);
	set_keys_movs(&rl->keys, &rl->movs);
	return (TRUE);
}
