/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cfgparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 19:55:35 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/01 20:17:44 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bp.h"

void	parsestuff(char *cfg, char *line)
{
	char	**splts;

	(void)line;
	splts = ft_strsplit(cfg, ';');
	ft_puttab(splts, NULL);
}
