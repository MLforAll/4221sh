#!/bin/sh

make -C ../..
gcc -c *.c -I . -I ../../includes -I ../../libft/includes -I ../../libftreadline/includes
objs=$(find ../../objs -type f -name "*.o")
filteredObjs=$(echo "$objs" | sed 's/\.\.\/\.\.\/objs\/sh_main.o//g')
gcc -o test_prgm *.o $filteredObjs -L ../../libft -L ../../libftreadline -lft -lftreadline -ltermcap
