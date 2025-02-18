NAME				=	ft_libc.a

CC 					=	@clang
INCLUDES_PATH		=	../../includes
CFLAGS 				=	-Wall -Werror -Wextra -fPIE -I$(INCLUDES_PATH)

COPY				=	@cp $@ $(NAME)
AR					=	@ar

SRCS_PATH			=	./srcs

FT_FPRINTF_PATH 	=	$(SRCS_PATH)/ft_fprintf/
LIBFT_PATH			=	$(SRCS_PATH)/libft/
GNL_PATH			=	$(SRCS_PATH)/get_next_line/
STRINGS_PATH		=	$(SRCS_PATH)/strings/
GARBAGE_PATH		=	$(SRCS_PATH)/garbage_collector/

SRCS				=	$(LIBFT_PATH)\
						$(FT_FPRINTF_PATH)\
						$(GNL_PATH)\
						$(STRINGS_PATH)\
						$(GARBAGE_PATH)

ifeq ($(SAFE), 1)
    CFLAGS += -DMALLOC=safe_malloc
else
	CFLAGS += -DMALLOC=malloc
endif

MAKE				=	make --no-print-directory\
							CFLAGS="$(CFLAGS)"\
							NAME=../../$(NAME) -C

all: $(NAME)

$(NAME): $(SRCS)
	@for src in $(SRCS); do \
		$(MAKE) $$src; \
	done;

clean			:
	@for src in $(SRCS); do \
		$(MAKE) $$src clean; \
	done;

fclean	:	clean
	@rm -rf $(NAME)

re				:	fclean all

bonus			:	all

.PHONY			:	run all dev re fclean clean bonus
