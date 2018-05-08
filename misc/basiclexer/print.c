/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 22:27:33 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/08 22:37:05 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "sh_lexer.h"
#include "libft.h"

static void	lstdelf(void *data, size_t datsize)
{
	(void)datsize;
	free(((t_token*)data)->toks);
	free(data);
}

static void	ft_putnchar_limit(char c, size_t len)
{
	char	buff[512];

	if (len > 512 || len == 0)
		return ;
	ft_memset(buff, c, len);
	write(STDOUT_FILENO, buff, len);
}

static void	print_tok(t_token *tok)
{
	static char	*typedesc[10] = {"NONE", "WORD", "IO_NUMBER", "PIPE",
								"GREAT", "DGREAT", "LESS", "DLESS",
								"CLOBBER", "AMPERSAND"};

	ft_putstr("Token: ");
	ft_putstr(typedesc[(int)tok->type]);
	ft_putnchar_limit(' ', 9 - ft_strlen(typedesc[(int)tok->type]));
	ft_putstr(" | Value: ");
	ft_putstr((tok->toks) ? tok->toks : "(null)");
	ft_putchar('\n');
}

void		print_tokens(char *line)
{
	t_list		*tokens;
	t_list		*tokbw;

	if (!(tokens = lex_line(line)))
	{
		ft_putendl_fd("tokens error", STDERR_FILENO);
		return ;
	}
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
	ft_lstdel(&tokens, &lstdelf);
}
