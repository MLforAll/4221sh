# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/16 17:49:56 by kdumarai          #+#    #+#              #
#    Updated: 2018/07/31 22:52:46 by kdumarai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = basicparser

all:
	../compile.sh $(NAME) ../../..

cleanp:
	rm -f *.o

fcleanp: cleanp
	rm -f $(NAME)

rep: fcleanp all

.PHONY: all cleanp fcleanp rep
