#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/31 13:03:51 by elbenkri          #+#    #+#              #
#    Updated: 2018/02/22 17:42:24 by elbenkri         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	=	ft_ls

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror #-g3 -fsanitize=address

SRCS	=	ft_parse.c \
			ft_open_path.c \
			ft_liste.c \
			ft_flags_g_maj.c \
			ft_flags_l.c \
			ft_flags_i.c \
			ft_affiche.c \
			ft_free_lst.c \
			ft_tri.c \
			ft_free_lst_libft.c \
			ft_print_file.c \
			ft_print_error.c \
			ft_print.c \
			main.c

OBJS	=	$(SRCS:.c=.o)

all: 		$(NAME)

$(NAME):	$(OBJS)
	@make -C libft/
	@$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME)

clean:
	@make -C libft/ clean
	@/bin/rm -rf $(OBJS)

fclean:	clean
	@make -C libft/	fclean
	@/bin/rm -rf $(NAME)

re: fclean all