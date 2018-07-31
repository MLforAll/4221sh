#!/bin/sh

if [ -z "$1" -o -z "$2" ]; then
	echo "Usage:"
	echo "	1/ Name"
	echo "	2/ 21sh Root"
	exit 1
fi

make -C $2
gcc -c *.c -I . -I $2/includes -I $2/libft/includes -I $2/libftreadline/includes
objs=$(find $2/objs -type f -name "*.o")
filteredObjs=$(echo "$objs" | sed "s|$2/objs/sh_main.o||g")
gcc -o $1 *.o $filteredObjs -L $2/libft -L $2/libftreadline -lft -lftreadline -ltermcap
