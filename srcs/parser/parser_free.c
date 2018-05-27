/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 19:22:56 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/28 00:26:01 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_parser.h"

static void	redirects_lstdel(void *data, size_t datasize)
{
	if (!data || datasize == 0)
		return ;
	free(((t_redirect*)data)->filename);
	free(data);
}

void		ast_btdel(void *data, size_t datsize)
{
	t_astnode	*ndat;
	t_cmdnode	*cmddat;

	if (!data || datsize == 0)
		return ;
	ndat = (t_astnode*)data;
	if (ndat->data)
	{
		cmddat = (t_cmdnode*)ndat->data;
		ft_tabfree(&cmddat->c_vars);
		free(cmddat->c_path);
		ft_tabfree(&cmddat->c_av);
		if (cmddat->c_redirects)
			ft_lstdel(&cmddat->c_redirects, &redirects_lstdel);
		free(ndat->data);
	}
	free(data);
}
