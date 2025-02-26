# Main
NAME				=	minishell
CC					=	clang

CFLAGS				=	-Wall -Werror -Wextra -Idependencies/ft_libc/includes  -Iincludes -fPIE
READLINE_FLAG		=	-lreadline
RM					=	rm -rf
MAKE				=	make --no-print-directory -C

# Colors
RESET				=	\033[0m
BLACK				=	\033[0;30m
RED					=	\033[0;31m
GREEN				=	\033[1;32m
YELLOW				=	\033[0;33m
BLUE				=	\033[0;34m
PURPLE				=	\033[1;35m
CYAN				=	\033[1;36m
WHITE				=	\033[0;37m

# Symbols
OK					=	✓
FAIL				=	✗
INFO				=	ⓘ

# Sources and Objects
FT_LIBC 			= ./dependencies/ft_libc/ft_libc.a

SRCS				=	src/main.c\
						src/prompt/get.c\
						src/utils/str/ft_str_only_contain.c\
						src/utils/array/len.c\
						src/utils/array/sort.c\
						src/utils/btree/create.c\
						src/utils/btree/foreach.c\
						src/utils/btree/type_foreach.c\
						src/utils/btree/get.c\
						src/utils/numbers/is_number.c\
						src/utils/numbers/max.c\
						src/paths/get.c\
						src/paths/set.c\
						src/paths/combine.c\
						src/parsing/parsing.c\
						src/initialisation/init.c\
						src/line/readline.c\
						src/signals/signals.c\
						src/signals/exit_codes.c\
						src/execution/pipeline.c\
						src/execution/errors.c\
						src/execution/commands/execute.c\
						src/execution/commands/bind.c\
						src/execution/commands/wait.c\
						src/execution/redirections/bind.c\
						src/execution/btree_logic.c\
						src/execution/redirections/heredocs.c\
						src/execution/checks/redirections.c\
						src/execution/built_in/built_in.c\
						src/execution/built_in/shlvl.c\
						src/execution/built_in/commands/cd.c\
						src/execution/built_in/commands/export.c\
						src/execution/built_in/commands/unset.c\
						src/execution/built_in/commands/env.c\
						src/execution/built_in/commands/pwd.c\
						src/execution/built_in/commands/exit.c\
						src/execution/built_in/commands/echo.c\
						src/execution/pipes/get.c\
						src/execution/pipes/set.c\
						src/execution/pipes/links/commands.c\
						src/execution/pipes/links/redirections.c\
						src/execution/pipes/utils/safe_close.c\
						src/execution/execution.c\
						src/execution/debug.c\
						src/env/utils.c\
						src/env/get.c\
						src/env/set.c

SRC_COUNT			=	$(words $(SRCS))

OBJS				=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

OBJ_DIR				=	objects

ifeq ($(GOOD_LOOKING_MESSAGES), 1)
	CFLAGS += -DGOOD_LOOKING_MESSAGES=1
endif

all : $(NAME)

$(NAME) : header $(FT_LIBC) $(OBJ_DIR)
		@$(CC) $(CFLAGS) $(READLINE_FLAG) $(OBJS) $(FT_LIBC) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) -c $< -o $@
		@printf "$(GREEN)$(OK)$(RESET)"

$(OBJ_DIR): $(OBJS)
		@if [ ! -d "$(OBJ_DIR)" ]; \
			then mkdir -p "$(OBJ_DIR)"; \
		fi
		@if [ ! -e "$(NAME)" ]; then \
			printf "]" ; \
			printf "\n" ; \
		fi

$(FT_LIBC) :
	@if [ ! -e "$(shell dirname $@)" ]; then \
		git clone git@github.com:R0-main/ft_libc.git $(shell dirname $@); \
	fi;
	@$(MAKE) $(shell dirname $@) SAFE=1

dev	 : clean-objs all
	valgrind --suppressions=readline.supp -s --track-fds=yes --trace-children=yes --show-leak-kinds=all --leak-check=full ./minishell

header:
		@printf "\
		        .__       .__       .__           .__  .__\n\
		  _____ |__| ____ |__| _____|  |__   ____ |  | |  |\n\
		 /     \|  |/    \|  |/  ___/  |  \_/ __ \|  | |  |\n\
		|  Y Y  \  |   |  \  |\___ \|   Y  \  ___/|  |_|  |__\n\
		|__|_|  /__|___|  /__/____  >___|  /\___  >____/____/\n\
		      \/        \/        \/     \/     \/\n\
		" ;
		@printf  "\n";
		@if [ ! -e "$(NAME)" ]; \
			then printf "Compiling Project : ["; \
		fi

clean-objs :
		@$(RM) $(OBJ_DIR)

clean : clean-objs
		@$(MAKE) $(shell dirname $(FT_LIBC)) fclean

fclean : clean
		@$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re header
