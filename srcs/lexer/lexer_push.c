/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 16:13:18 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/21 20:35:12 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

/*inline static void	quote_removal(char *s, t_tab *qidx)
{
	char			*tmp;
	unsigned long	idx;

	idx = qidx->count;
	while (TRUE)
	{
		if (*(tmp = s + ((int*)(qidx->data))[--idx]))
			ft_strcpy(tmp, tmp + 1);
		if (idx == 0)
			break ;
	}
}*/

static t_quoting	detect_quote(char c, unsigned long *idx, t_quoting curr)
{
	if (c == '\\' && curr == kDQuote)
	{
		(*idx)++;
		return (kDQuote);
	}
	if (c == '"')
		return (curr == kDQuote ? kQuoteNone : kDQuote);
	if (c == '\'')
		return (curr == kSQuote ? kQuoteNone : kSQuote);
	return (curr);
}

static char			*do_expansions(char *s)
{
	t_quoting		curr;
	t_quoting		old;
	unsigned long	idx;
	t_str			vs;

	vs = ft_tstrnew();
	idx = 0;
	old = kQuoteNone;
	curr = kQuoteNone;
	while (s[idx])
	{
		if ((curr = detect_quote(s[idx], &idx, curr)) == old)
		{
			if (s[idx] == '$' && curr != kSQuote)
				ft_putendl("var exp");
			ft_tstrncat(&vs, s + idx, 1);
		}
		old = curr;
		idx++;
	}
	return (vs.s);
}

void				add_token(t_dlist **tokens,
							t_str *vs,
							t_toktype type,
							int prio)
{
	t_dlist	*newtok;
	t_token	tokdat;
	/*char	*cpy;
	int		cpy_isalloced;*/

	if (!vs || (ft_strlen(vs->s) < 1))
		return ;
	ft_bzero(&tokdat, sizeof(t_token));
	if (!(tokdat.s = do_expansions(vs->s)))
		return ;
	/*cpy = vs->s;
	cpy_isalloced = (lexer_expand_tilde(&cpy) || lexer_expand_var(&cpy));
	if (!(tokdat.s = ft_strdup(cpy)))
		return ;*/
	tokdat.type = type;
	tokdat.priority = prio;
	if (!(newtok = ft_dlstnew(&tokdat, sizeof(t_token))))
		return ;
	/*if (cpy_isalloced)
		free(cpy);*/
	ft_dlstpush(tokens, newtok);
	ft_tstrclr(vs);
}
