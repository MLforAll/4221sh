# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/20 21:41:19 by kdumarai          #+#    #+#              #
#    Updated: 2018/05/17 00:00:32 by kdumarai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CC_FLAGS = -Wall -Werror -Wextra
CC_LIB = -I includes -I libft/includes -I libftreadline/includes
LD_FLAGS = -L libft -L libftreadline -lft -lftreadline -ltermcap

LIBFT = libft/libft.a
LIBFTREADLINE = libftreadline/libftreadline.a

INCDIR = includes
INCFILES = sh.h \
		   sh_data.h \
		   sh_prompt.h \
INCLUDES = $(addprefix $(INCDIR)/, $(INCFILES))

SRCDIR = srcs
SRCFILES = sh_main.c \
	sh_eshell.c \
	sh_ishell.c \
	sh_eval.c \
	sh_cmdexec.c \
	sh_cmdredirs.c \
	sh_err.c \
	parser/parser_start.c \
	parser/parser_cmd.c \
	parser/parser_free.c \
	parser/parser_heredocs.c \
	lexer/lexer_start.c \
	lexer/lexer_general.c \
	lexer/lexer_dquote.c \
	lexer/lexer_great.c \
	lexer/lexer_less.c \
	lexer/lexer_ampersand.c \
	lexer/lexer_switch.c \
	prompt/sh_prompt.c \
	prompt/sh_prompt_helpers.c \
	env/sh_env.c \
	env/sh_env_helpers.c \
	fsexp_functions.c \
	bltns/sh_builtins.c \
	bltns/sh_env_bltncmd.c \
	bltns/sh_cd_bltncmd.c \
	misc/sh_misc.c \
	misc/sh_misc_str.c \
	misc/lst_support.c \
	misc/tlist_support.c
SRCS = $(addprefix $(SRCDIR)/, $(SRCFILES))
NSRC = $(shell echo "$(SRCFILES)" | awk '{print NF}')
ifeq ($(shell [ ! -z "`which bc`" ] && [ ! -z "`which awk`" ] && echo true),true)
	CSRC = 1
else
	CSRC = 0
endif

OBJDIR = objs
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

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

$(OBJDIR)/%.o: $(SRCDIR)/%.c
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
