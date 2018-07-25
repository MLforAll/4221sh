/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 16:13:18 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/25 04:11:44 by kdumarai         ###   ########.fr       */
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

/*
** todo: proper reversal of condition (cleaner stmt), line 63-64
*/

static int				cpy_string(char *s, t_str *vs, t_list **ret)
{
	t_quoting		curr;
	t_quoting		old;
	int				rval;

	old = kQuoteNone;
	curr = kQuoteNone;
	rval = FALSE;
	while (*s)
	{
		if ((curr = detect_quote(s, curr)) != kQuoteNone && curr != kEscape)
			rval = TRUE;
		if (curr == old && !(*s == '$' && curr != kSQuote \
							&& lexer_expand_var(&s, vs, ret, curr)))
			(void)ft_tstrncat(vs, s, 1);
		if (curr == kEscape)
		{
			if (s[1] == '"' && !ft_tstrncat(vs, ++s, 1))
				return (-1);
			curr = old;
		}
		old = curr;
		s++;
	}
	return (rval);
}

static t_uint8			get_tokens_strings(t_list **ret, char *s)
{
	t_list			*new;
	t_str			vs;
	int				cpy_rval;

	(void)ft_tstrnew(&vs);
	*ret = NULL;
	(void)lexer_expand_tilde(&s, &vs);
	if ((cpy_rval = cpy_string(s, &vs, ret)) == -1
		|| ((*vs.s || cpy_rval) && !(new = ft_lstnew(vs.s, vs.len + 1))))
	{
		ft_lstdel(ret, &ft_lstnodefree);
		return (FALSE);
	}
	else if (*vs.s || cpy_rval)
		ft_lstpush(ret, new);
	ft_tstrdel(&vs);
	return (TRUE);
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

	if (!vs || vs->len < 1)
		return ;
	if (!get_tokens_strings(&tokstrs, vs->s))
		return ;
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
