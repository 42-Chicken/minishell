NAME				=	libftfprintf.a

INCLUDES_PATH		=	./includes
CC					=	cc
CFLAGS				=	-Wall -Werror -Wextra -I$(INCLUDES_PATH)

SRCS				=	./src/ft_fprintf.c\
						./src/ft_unsigned_putnbr.c\
						./src/ft_print_hex.c\
						./src/processing/address.c\
						./src/processing/char.c\
						./src/processing/hex.c\
						./src/processing/num.c\
						./src/processing/str.c\
						./src/processing/unsigned_num.c\

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
