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
						src/utils/btree/create.c\
						src/utils/btree/foreach.c\
						src/utils/btree/get.c\
						src/paths/get.c\
						src/paths/set.c\
						src/paths/combine.c\
						src/parsing/parsing.c\
						src/initialisation/init.c\
						src/line/readline.c\
						src/signals/signals.c\
						src/signals/exit_codes.c\
						src/execution/pipeline.c\
						src/execution/pipes/get.c\
						src/execution/pipes/set.c\
						src/execution/pipes/link.c\
						src/execution/pipes/utils/safe_close.c\
						src/execution/debug.c\
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

dev	 : re
	valgrind --suppressions=readline.supp -s --show-leak-kinds=all --leak-check=full ./minishell

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

clean :
		@$(RM) $(OBJ_DIR)
		@$(MAKE) $(shell dirname $(FT_LIBC)) fclean

fclean : clean
		@$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re header
