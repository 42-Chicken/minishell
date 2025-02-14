NAME				=	garbadge_collector.a

INCLUDES_PATH		=	./includes
CC					=	cc
CFLAGS				=	-Wall -Werror -Wextra -I$(INCLUDES_PATH)

START_COLOR			=	\033[38;2;

COLOUR_GREEN		=	${START_COLOR}10;255;1m
COLOUR_YELLOW		=	${START_COLOR}255;255;1m
COLOUR_ORANGE		=	${START_COLOR}150;20;20m
COLOUR_PURPLE		=	${START_COLOR}175;50;150m
COLOUR_RED			=	${START_COLOR}255;0;0m

SRCS				=	garbadge.c \
						safe_exit.c\
						safe_free.c\
						safe_malloc.c\
						context.c\
						utils.c\

OBJS				=	${SRCS:.c=.o}

all: ${NAME}

${NAME} : ${OBJS}
	@ar rcs $@ $^

%.o : %.c
	@${CC} ${CFLAGS} -c $<

clean:
	@rm -rf ${OBJS}

fclean:	clean
	@rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
