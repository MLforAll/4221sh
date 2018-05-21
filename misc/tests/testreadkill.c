/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testreadkill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 04:10:05 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/15 04:27:59 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

struct termios saved_t;

static void	fct(int sigc)
{
	struct termios	t;

	(void)sigc;
	puts("Received signal");
	t = saved_t;
	t.c_lflag &= ~ICANON;
	t.c_cc[VMIN] = 0;
	t.c_cc[VTIME] = 2;
	tcsetattr(0, TCSANOW, &t);
}

int		main(void)
{
	char	buff[256];
	ssize_t	rb;

	tcgetattr(0, &saved_t);
	signal(SIGUSR1, &fct);
	while ((rb = read(0, buff, 256)) > 0)
		write(1, buff, rb);
	tcsetattr(0, TCSANOW, &saved_t);
	return 0;
}
