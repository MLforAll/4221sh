/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 17:30:16 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/05 17:33:45 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "../basiclexer/bl.h"

void	lstdelf(void *data, size_t datsize)
{
	(void)datsize;
	free(((t_token*)data)->toks);
	free(data);
}

void	astputelem(void *data, size_t datsize)
{
	if (datsize == 0)
	{
		ft_putendl("maybe t_list");
		return ;
	}
	ft_putendl((char*)data);
}
