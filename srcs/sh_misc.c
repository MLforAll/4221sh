/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 18:31:09 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/28 14:57:33 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		free_return(void **data, int retv)
{
	if (data && *data)
	{
		free(*data);
		*data = NULL;
	}
	return (retv);
}

int		ft_strchrf(const char *s, char c)
{
	unsigned long	last;
	unsigned long	idx;

	idx = 0;
	last = 0;
	while (s[idx])
	{
		if (s[idx] == c && idx == last + 1)
			return (TRUE);
		if (s[idx] == c)
			last = idx;
		idx++;
	}
	return (FALSE);
}
