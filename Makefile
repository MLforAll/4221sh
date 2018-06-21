# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/20 21:41:19 by kdumarai          #+#    #+#              #
#    Updated: 2018/06/21 16:56:04 by kdumarai         ###   ########.fr        #
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
		   sh_lexer.h \
		   sh_parser.h \
		   sh_builtins.h \
		   sh_jobs.h
INCLUDES = $(addprefix $(INCDIR)/, $(INCFILES))

SRCDIR = srcs
SRCFILES = sh_main.c \
	sh_eshell.c \
	sh_ishell.c \
	sh_eval.c \
	sh_err.c \
	sh_hist_loadsave.c \
	exec/sh_cmdexec.c \
	exec/sh_cmdredirs.c \
	exec/sh_cmdpipes.c \
	jobs/sh_jobs.c \
	jobs/sh_jobs_helper.c \
	jobs/sh_jobs_sigchld.c \
	jobs/sh_jobs_async.c \
	autocompletion/sh_acget.c \
	autocompletion/sh_acshow.c \
	parser/parser_start.c \
	parser/parser_cmd.c \
	parser/parser_pathget.c \
	parser/parser_free.c \
	parser/parser_readagain.c \
	parser/parser_syntax.c \
	lexer/lexer_start.c \
	lexer/lexer_general.c \
	lexer/lexer_dquote.c \
	lexer/lexer_great.c \
	lexer/lexer_less.c \
	lexer/lexer_semipipe.c \
	lexer/lexer_ampersand.c \
	lexer/lexer_switch.c \
	lexer/lexer_expansion.c \
	prompt/sh_prompt.c \
	prompt/sh_prompt_helpers.c \
	vars/sh_env.c \
	vars/sh_env_helpers.c \
	vars/sh_lvars.c \
	bltns/sh_builtins.c \
	bltns/sh_echo_bltncmd.c \
	bltns/sh_exit_bltncmd.c \
	bltns/sh_source_bltncmd.c \
	bltns/sh_cd_bltncmd.c \
	bltns/sh_env_bltncmd.c \
	bltns/sh_bltn_utils.c \
	bltns/sh_setenv_bltncmd.c \
	bltns/sh_jobs_bltncmd.c \
	misc/sh_misc.c \
	misc/sh_misc_str.c \
	misc/tlist_support.c \
	fsexp_functions.c
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

cleanp:
	@ rm -rf $(OBJDIR)
	@ printf "$(PROJTEXT)Removed objects\n"

fcleanp: cleanp
	@ rm -f $(NAME)
	@ printf "$(PROJTEXT)Removed $(NAME)\n"

rep: fcleanp all

clean: cleanp
	@ make clean -C $(dir $(LIBFT))
	@ make clean -C $(dir $(LIBFTREADLINE))

fclean: fcleanp
	@ make fclean -C $(dir $(LIBFT))
	@ make fclean -C $(dir $(LIBFTREADLINE))

re: fclean all

force:
	@ true

.PHONY: all noflags fsanitize clean fclean re cleanp fcleanp rep force
