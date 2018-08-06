/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 19:22:56 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/06 22:22:25 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh_parser.h"

static void	redirects_lstdel(void *data, size_t datasize)
{
	if (!data || datasize == 0)
		return ;
	free(((t_redirect*)data)->data);
	free(data);
}

void		cmdnode_free(t_cmdnode *cmddat)
{
	ft_tabfree(&cmddat->c_vars);
	free(cmddat->c_path);
	ft_tabfree(&cmddat->c_av);
	if (cmddat->c_redirects)
		ft_lstdel(&cmddat->c_redirects, &redirects_lstdel);
	free(cmddat);
}

void		ast_btdel(void *data, size_t datsize)
{
	t_astnode	*ndat;

	if (!data || datsize == 0)
		return ;
	ndat = (t_astnode*)data;
	if (ndat->data)
		cmdnode_free((t_cmdnode*)ndat->data);
	free(data);
}
