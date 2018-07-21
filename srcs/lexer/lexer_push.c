/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 16:13:18 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/21 07:38:55 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

inline static void	quote_removal(char *s, t_tab *qidx)
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
}

static t_quoting	detect_quote(char c, unsigned long *idx, t_quoting curr,
								t_tab *qidx)
{
	if (c == '\\' && curr == kDQuote)
	{
		ft_ttabcat(qidx, idx, 1);
		(*idx)++;
		return (kDQuote);
	}
	if (c == '"')
	{
		ft_ttabcat(qidx, idx, 1);
		return (curr == kDQuote ? kQuoteNone : kDQuote);
	}
	if (c == '\'')
	{
		ft_ttabcat(qidx, idx, 1);
		return (curr == kSQuote ? kQuoteNone : kDQuote);
	}
	return (curr);
}

static void			do_expansions(char *s)
{
	t_tab			qidx;
	t_quoting		curr;
	unsigned long	idx;

	idx = 0;
	curr = kQuoteNone;
	qidx = ft_ttabnew(sizeof(int));
	while (s[idx])
	{
		curr = detect_quote(s[idx], &idx, curr, &qidx);
		idx++;
	}
	if (qidx.count > 0)
		quote_removal(s, &qidx);
	ft_ttabdel(&qidx, NULL);
}

void				add_token(t_dlist **tokens,
							t_str *vs,
							t_toktype type,
							int prio)
{
	t_dlist	*newtok;
	t_token	tokdat;
	char	*cpy;
	int		cpy_isalloced;

	do_expansions(vs->s);
	if (!vs || (ft_strlen(vs->s) < 1))
		return ;
	ft_bzero(&tokdat, sizeof(t_token));
	cpy = vs->s;
	cpy_isalloced = (lexer_expand_tilde(&cpy) || lexer_expand_var(&cpy));
	if (!(tokdat.s = ft_strdup(cpy)))
		return ;
	tokdat.type = type;
	tokdat.priority = prio;
	if (!(newtok = ft_dlstnew(&tokdat, sizeof(t_token))))
		return ;
	if (cpy_isalloced)
		free(cpy);
	ft_dlstpush(tokens, newtok);
	ft_tstrclr(vs);
}
