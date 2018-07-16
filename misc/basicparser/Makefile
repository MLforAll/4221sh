# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/16 17:49:56 by kdumarai          #+#    #+#              #
#    Updated: 2018/07/16 17:51:38 by kdumarai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	./compile.sh

cleanp:
	rm -f *.o

fcleanp: cleanp
	rm -f test_prgm

rep: fcleanp all

.PHONY: all cleanp fcleanp rep
