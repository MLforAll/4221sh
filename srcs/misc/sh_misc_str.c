/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_misc_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 18:31:09 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/14 05:20:35 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		ft_strchrf(char *s, char c)
{
	unsigned int	last;
	unsigned int	idx;

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
