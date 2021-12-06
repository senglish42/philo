NAME	=	philo

INCL	=	./includes

SRCS	=	srcs/main.c

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-g -Wall -Werror -Wextra -I $(INCL)

RM		=	rm -rf

CC		=	gcc

HEADER	=	$(INCL)/philo.h

.PHONY: all clean fclean re

%.o:	%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(LIB):	libft/*.c	includes/libft.h
	make -C libft

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all