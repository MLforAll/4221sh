/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 16:13:18 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/20 16:37:58 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

void				add_token(t_dlist **tokens,
							t_str *vs,
							t_toktype type,
							int prio)
{
	t_dlist	*newtok;
	t_token	tokdat;
	char	*cpy;
	int		cpy_isalloced;

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
