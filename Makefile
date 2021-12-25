NAME	=	philo

INCL	=	includes

OBJ_DIR	=	.obj

SRCS_DIR=	srcs

SRCS	=	$(SRCS_DIR)/main.c		$(SRCS_DIR)/ft_split.c	$(SRCS_DIR)/utils.c\
			$(SRCS_DIR)/threads.c	$(SRCS_DIR)/lists.c		$(SRCS_DIR)/error.c\

OBJS	= 	$(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

CFLAGS	=	-g -pthread -Wall -Werror -Wextra -I $(INCL)

RM		=	rm -rf

CC		=	gcc

HEADER	=	$(INCL)/philo.h

.PHONY: all clean fclean re

$(OBJ_DIR)/%.o:%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/$(SRCS_DIR)
	@$(CC) -c $(CFLAGS) $< -o $@

all:	$(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)


clean:
			@ $(RM) $(OBJ_DIR)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all