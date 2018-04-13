#!/bin/sh

if [ ! -f libftreadline_tester.c ]; then
	echo "OOPS!"
	echo "Not in right folder!"
	echo "You are here: $PWD"
	exit 1
fi

make -C ../../libft
make -C ../../libftreadline
gcc -o libftreadline_tester libftreadline_tester.c -I ../../libft -I ../../libftreadline/includes -L ../../libft -L ../../libftreadline -lft -lftreadline -ltermcap
