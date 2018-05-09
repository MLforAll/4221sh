# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/20 21:41:19 by kdumarai          #+#    #+#              #
#    Updated: 2018/05/09 22:19:11 by kdumarai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = basicparser

CC_FLAGS = -Wall -Werror -Wextra
CC_LIB = -I . -I ../../libft/includes -I ../../libftreadline/includes
LD_FLAGS = -L ../../libft -L ../../libftreadline -lft -lftreadline -ltermcap

LIBFT = ../../libft/libft.a
LIBFTREADLINE = ../../libftreadline/libftreadline.a

SRCS = main.c \
	parsemain.c \
	utils.c \
	../basiclexer/lexer_start.c \
	../basiclexer/lexer_general.c \
	../basiclexer/lexer_dquote.c \
	../basiclexer/lexer_great.c \
	../basiclexer/lexer_less.c \
	../basiclexer/lexer_switch.c

NSRC = $(shell echo "$(SRCS)" | awk '{print NF}')
ifeq ($(shell [ ! -z "`which bc`" ] && [ ! -z "`which awk`" ] && echo true),true)
	CSRC = 1
else
	CSRC = 0
endif

OBJDIR = objs
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

PROJTEXT = \033[1;33m$(NAME): \033[0;39m

all: $(NAME)

$(LIBFT): force
	@ make -C $(dir $(LIBFT))

$(LIBFTREADLINE): force
	@ make -C $(dir $(LIBFTREADLINE))

$(NAME): $(LIBFT) $(LIBFTREADLINE) $(OBJS) $(INCLUDES)
	@ printf "\033[K$(PROJTEXT)Compiling\n"
	@ printf "$(PROJTEXT)Linking\n"
	@ gcc -o $(NAME) $(LD_FLAGS) $(OBJS)
	@ printf "$(PROJTEXT)\033[1;32mProgram built at $(NAME)\033[0;39m\n"

noflags:
	@ printf "\033[1;31m----------------------\n"
	@ printf "| CC_FLAGS DISABLED! |\n"
	@ printf "\r----------------------\033[0;39m\n"
	@ make all CC_FLAGS=""

fsanitize:
	@ printf "\033[1;31m------------------------------\n"
	@ printf "\r| ADDRESS SANITIZER ENABLED! |\n"
	@ printf "\r------------------------------\033[0;39m\n"
	@ make all LD_FLAGS="$(LD_FLAGS) -fsanitize=address"

$(OBJDIR)/%.o: %.c
	@ if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	@ printf "\033[K$(PROJTEXT)Compiling \033[1;33m$<"
ifneq ($(CSRC),0)
	@ printf " %.0s" {1..$(shell expr 44 - $(shell printf "$<" | wc -m))}
	@ export LC_ALL=C; printf "\033[1;34m[%3.0f%%]" "$(shell bc <<< "scale=1; $(CSRC) / $(NSRC) * 100")"
	@ $(eval CSRC = $(shell expr $(CSRC) + 1))
endif
	@ printf "\033[0;39m\r"
	@ gcc $(CC_FLAGS) $(CC_LIB) -c $< -o $@

clean:
	@ make clean -C $(dir $(LIBFT))
	@ make clean -C $(dir $(LIBFTREADLINE))
	@ rm -rf $(OBJDIR)
	@ printf "$(PROJTEXT)Removed objects\n"

fclean: clean
	@ make fclean -C $(dir $(LIBFT))
	@ make fclean -C $(dir $(LIBFTREADLINE))
	@ rm -f $(NAME)
	@ printf "$(PROJTEXT)Removed $(NAME)\n"

re: fclean all

force:
	@ true

.PHONY: all noflags fsanitize clean fclean re force
