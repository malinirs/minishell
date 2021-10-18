NAME	=	minishell
HEADER	=	minishell.h
SOURCE	=	main.c \
			utils_1.c \
#
SRCS	=	$(SOURCE)
OBJS	=	$(SRCS:.c=.o)
GCC		=	gcc
RM		=	rm -f
CFLAGS	=	-Wall -Wextra -Werror

all: $(NAME)

.c.o:
		$(GCC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS) $(HEADER)
		$(MAKE) -C ./libft
		$(GCC) $(CFLAGS) $(OBJS) Libft/libft.a -o $(NAME)

clean:
				$(MAKE) clean -C ./libft
				$(RM) $(OBJS)

fclean:			clean
				$(MAKE) fclean -C ./libft
				$(RM) $(NAME)

re:				fclean all

.PHONE:	all clean fclean
