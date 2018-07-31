/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 22:27:33 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/31 22:50:33 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "blintern.h"
#include "g_typedesc.h"

static void	ft_putnchar_limit(char c, size_t len)
{
	char	buff[512];

	if (len > 512 || len == 0)
		return ;
	(void)ft_memset(buff, c, len);
	(void)write(STDOUT_FILENO, buff, len);
}

static void	print_tok(t_token *tok)
{
	ft_putstr("Token: ");
	if ((unsigned long)tok->type < sizeof(g_typedesc) / sizeof(*g_typedesc))
		ft_putstr(g_typedesc[(int)tok->type]);
	else
		ft_putstr("Undefined");
	ft_putnchar_limit(' ', 10 - ft_strlen(g_typedesc[(int)tok->type]));
	ft_putstr(" | Value: ");
	ft_putstr((tok->s) ? tok->s : "(null)");
	ft_putchar('\n');
}

void		print_tokens(char *line)
{
	int			lex_ret;
	t_dlist		*tokens;
	t_dlist		*tokbw;

	tokens = NULL;
	if ((lex_ret = lex_line(&tokens, line)) == LEXER_FAIL)
	{
		ft_putendl_fd("tokens error", STDERR_FILENO);
		return ;
	}
	if (lex_ret > LEXER_OK)
		ft_putendl_fd("should read again", STDERR_FILENO);
	ft_putendl("------------------------------------");
	ft_putendl("|               tokens             |");
	ft_putendl("------------------------------------");
	tokbw = tokens;
	while (tokbw)
	{
		print_tok((t_token*)tokbw->content);
		tokbw = tokbw->next;
	}
	ft_putendl("------------------------------------");
	ft_dlstdel(&tokens, &tokens_lstdel);
}
