/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 16:13:18 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/23 19:33:41 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

/*
**inline static void	quote_removal(char *s, t_tab *qidx)
**{
**	char			*tmp;
**	unsigned long	idx;
**
**	idx = qidx->count;
**	while (TRUE)
**	{
**		if (*(tmp = s + ((int*)(qidx->data))[--idx]))
**			(void)ft_strcpy(tmp, tmp + 1);
**		if (idx == 0)
**			break ;
**	}
**}
*/

inline static t_quoting	detect_quote(char *s, t_quoting curr)
{
	if (*s == '\\'
		&& ((curr == kDQuote && (s[1] == '$' || s[1] == '"' || s[1] == '\\'))
			|| (curr != kDQuote && s[1])))
		return (kEscape);
	if (*s == '"')
		return (curr == kDQuote ? kQuoteNone : kDQuote);
	if (*s == '\'')
		return (curr == kSQuote ? kQuoteNone : kSQuote);
	return (curr);
}

static t_list			*get_tokens_strings(char *s)
{
	t_list			*ret;
	t_list			*new;
	t_quoting		curr;
	t_quoting		old;
	t_str			vs;

	vs = ft_tstrnew();
	ret = NULL;
	old = kQuoteNone;
	curr = kQuoteNone;
	(void)lexer_expand_tilde(&s, &vs);
	while (*s)
	{
		if ((curr = detect_quote(s, curr)) == old)
		{
			// todo: proper reversal of condition (cleaner stmt)
			if (!(*s == '$' && curr != kSQuote && lexer_expand_var(&s, &vs)))
				(void)ft_tstrncat(&vs, s, 1);
		}
		if (curr == kEscape)
		{
			if (s[1] == '"')
				(void)ft_tstrncat(&vs, ++s, 1);
			curr = old;
		}
		old = curr;
		s++;
	}
	new = ft_lstnew_nomalloc(vs.s, ft_strlen(vs.s) + 1);
	ft_lstpush(&ret, new);
	return (ret);
}

void					add_token(t_dlist **tokens,
								t_str *vs,
								t_toktype type,
								int prio)
{
	t_dlist	*newtok;
	t_token	tokdat;
	t_list	*tokstrs;
	t_list	*toksbw;

	if (!vs || (ft_strlen(vs->s) < 1))
		return ;
	tokstrs = get_tokens_strings(vs->s);
	toksbw = tokstrs;
	while (toksbw)
	{
		ft_bzero(&tokdat, sizeof(t_token));
		tokdat.s = (char*)toksbw->content;
		tokdat.type = type;
		tokdat.priority = prio;
		if (!(newtok = ft_dlstnew(&tokdat, sizeof(t_token))))
			return ;
		ft_dlstpush(tokens, newtok);
		toksbw = toksbw->next;
	}
	ft_lstdel(&tokstrs, NULL);
	ft_tstrclr(vs);
}
