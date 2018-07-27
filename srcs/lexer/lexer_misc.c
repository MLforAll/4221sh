/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_switch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 23:11:41 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/27 04:58:56 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_lexer.h"

int			ft_swcmp(const void *p1, const void *p2)
{
	return (*(const int*)p1 == *(const int*)p2);
}

void		tokens_lstdel(void *data, size_t datsize)
{
	(void)datsize;
	free(((t_token*)data)->s);
	free(data);
}
