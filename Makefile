NAME	=	ft_ls

CC	=	gcc

CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	ft_parse.c \
		ft_open_path.c \
		ft_liste.c \

OBJS	=	$(SRCS:.c=.o)

all: 		$(NAME)

$(NAME):	$(OBJS)
	@make -C libft/
	@$(CC) $(CFLAGS) $(OBJS) main.c libft/libft.a -o $(NAME)

clean:
	@make -C libft/ clean
	@/bin/rm $(OBJS)

fclean:	clean
	@make -C libft/	fclean
	@/bin/rm $(NAME)

re: fclean all