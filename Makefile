# Main
NAME				=	minishell
CC					=	gcc

CFLAGS				=	-Wall -Werror -Wextra -Idependencies/ft_libc/includes -Iincludes -fPIE
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
		@$(CC) $(CFLAGS) $(OBJS) $(FT_LIBC) -o $(NAME)

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
