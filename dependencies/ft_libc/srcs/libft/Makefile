NAME				=	libft.a

INCLUDES_PATH		=	./includes
CC					=	cc
CFLAGS				=	-Wall -Werror -Wextra -I$(INCLUDES_PATH)

START_COLOR			=	\033[38;2;

COLOUR_GREEN		=	${START_COLOR}10;255;1m
COLOUR_YELLOW		=	${START_COLOR}255;255;1m
COLOUR_ORANGE		=	${START_COLOR}150;20;20m
COLOUR_PURPLE		=	${START_COLOR}175;50;150m
COLOUR_RED			=	${START_COLOR}255;0;0m

BONUS_SRCS			=	ft_lstadd_back.c \
						ft_lstadd_front.c \
						ft_lstdelone.c \
						ft_lstlast.c \
						ft_lstnew.c \
						ft_lstsize.c \
						ft_lstclear.c \
						ft_lstiter.c \
						ft_lstmap.c

SRCS				=	ft_atoi.c \
						ft_bzero.c \
						ft_calloc.c \
						ft_isalnum.c \
						ft_isalpha.c \
						ft_isascii.c \
						ft_isdigit.c \
						ft_isprint.c \
						ft_itoa.c \
						ft_memchr.c \
						ft_memcmp.c \
						ft_memcpy.c \
						ft_memmove.c \
						ft_memset.c \
						ft_putchar_fd.c \
						ft_putendl_fd.c \
						ft_putnbr_fd.c \
						ft_putstr_fd.c \
						ft_split.c \
						ft_strchr.c \
						ft_strdup.c \
						ft_striteri.c \
						ft_strjoin.c \
						ft_strlcat.c \
						ft_strlcpy.c \
						ft_strlen.c \
						ft_strmapi.c \
						ft_strncmp.c \
						ft_strnstr.c \
						ft_strrchr.c \
						ft_strtrim.c \
						ft_substr.c \
						ft_tolower.c \
						ft_toupper.c

OBJS				=	${SRCS:.c=.o}
BONUS_OBJS			=	${BONUS_SRCS:.c=.o}

all: ${NAME}

${NAME} : ${OBJS} ${BONUS_OBJS}
	@ar rcs $@ $^

bonus: ${OBJS} ${BONUS_OBJS}
	@ar rcs ${NAME} $^

%.o : %.c
	@${CC} ${CFLAGS} -c $<

clean:
	@rm -rf ${OBJS} ${BONUS_OBJS}

fclean:	clean
	@rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
