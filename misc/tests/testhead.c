/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testhead.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 23:33:16 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/06 23:39:52 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

void	hdl(int sigc)
{
	if (sigc != SIGPIPE)
		return ;
	(void)write(2, "HEAD_SIGPIPE\n", 13);
}

int main(int ac, char **av)
{
	int		n;
	char	c;

	if (ac < 2)
		return (1);
	(void)signal(SIGPIPE, &hdl);
	n = atoi(av[1]);
	while (n--)
	{
		if (read(0, &c, 1) != 1)
			break ;
		(void)write(1, &c, 1);
	}
	(void)write(2, "HEAD_QUIT\n", 10);
	return (0);
}
