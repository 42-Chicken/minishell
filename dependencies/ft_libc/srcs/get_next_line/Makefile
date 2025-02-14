NAME				=	gnl.a

INCLUDES_PATH		=	./includes
CC					=	cc
CFLAGS				=	-Wall -Werror -Wextra -I$(INCLUDES_PATH)

SRCS				=	./get_next_line.c\
						./get_next_line_utils.c\

OBJS				=	$(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@ar rcs $@ $(OBJS)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

re: fclean all

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

.PHONY: fclean clean re all
