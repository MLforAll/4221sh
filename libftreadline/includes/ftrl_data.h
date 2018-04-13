/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 06:36:52 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/13 06:43:57 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTRL_DATA_H
# define FTRL_DATA_H

# include "libft.h"
# include <stdint.h>

/*
** linked list for history mgmt
*/

typedef struct	s_history
{
	char				*line;
	struct s_history	*next;
	struct s_history	*prev;
}				t_history;

/*
** options struct
*/

typedef struct	s_rl_opts
{
	uint8_t		bell;
	int			outfd;
	int			(*ac_get_result)(char *);
	t_list		(*ac_multi_choice)(t_list *);
	t_history	*hist;
}				t_rl_opts;

#endif
