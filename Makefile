NAME	=	minishell

SRCS		= 	main.c \
                utils_1.c \
                pars_dollar.c \
                pars_quotes.c \

OBJS		=	$(patsubst %.c,%.o,$(SRCS))

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -MMD
RM			=	rm -f

LIB			= ./Libft/libft.a
RDL			= -lreadline

all:		$(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) -c -g $< -o $@ $(INCLUDE)

$(NAME):	$(OBJS) $(OBJS_C)
			$(MAKE) -C $(dir $(LIB))
			$(CC) -o $(NAME) $(OBJS) $(LIB) $(RDL)

bonus:		$(NAME)

clean:
			$(RM) $(OBJS) $(OBJS:.o=.d)
			@make -C $(dir $(LIB)) clean

fclean:		clean
			@make -C $(dir $(LIB)) fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
-include	$(OBJS:.o=.d)








#NAME	=	minishell
#HEADER	=	minishell.h
#SOURCE	=	main.c \
#			utils_1.c \
#			pars_dollar.c \
#			pars_quotes.c \
##
#SRCS	=	$(SOURCE)
#OBJS	=	$(SRCS:.c=.o)
#GCC		=	gcc
#RM		=	rm -f
#CFLAGS	=	-Wall -Wextra -Werror
#
#all: $(NAME)
#
#.c.o:
#		$(GCC) $(CFLAGS) -c $< -o $(<:.c=.o)
#
#$(NAME): $(OBJS) $(HEADER)
#		$(MAKE) -C ./libft
#		$(GCC) $(CFLAGS) $(OBJS) Libft/libft.a -o $(NAME)
#
#clean:
#				$(MAKE) clean -C ./libft
#				$(RM) $(OBJS)
#
#fclean:			clean
#				$(MAKE) fclean -C ./libft
#				$(RM) $(NAME)
#
#re:				fclean all
#
#.PHONE:	all clean fclean
