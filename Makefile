NAME		=	minishell

SRCS		= 	main.c \
                utils_1.c \
                pars_dollar.c \
                pars_quotes.c \
                utils_list_1.c \
                creation_list.c \
                write_array.c \
                pre_parsing.c \
                delete_space.c \
                check_space_divider.c \
                divider.c \
                write_error.c \
                check_symbol.c \
                parsing.c \
				init_env.c \
				cmd_cd.c \
				cd_utils.c \
				cmd_echo.c \
				cmd_exit.c \
				cmd_export.c \
				export_sort.c \
				cmd_pwd.c \
				cmd_unset.c \
				cmd_utils.c \
				signal.c \
				main_job.c \
				get_next_line.c \
				process.c \
				output.c \



OBJS		=	$(patsubst %.c,%.o,$(SRCS))

HEADER		= ./minishell.h ./Libft/libft.h
INCLUDE		= -I ~/.brew/opt/readline/include
RDL			= -L ~/.brew/opt/readline/lib
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm -f

LIB			= ./Libft/libft.a

all:		$(NAME)

%.o : %.c	$(HEADER)
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o ${<:.c=.o}

$(NAME):	$(OBJS) $(HEADER)
			$(MAKE) -C Libft
			$(CC) -o $(NAME) $(INCLUDE)  $(OBJS) $(LIB) $(RDL) -lreadline

clean:
			$(RM) $(OBJS)
			@make -C $(dir $(LIB)) clean

fclean:		clean
			@make -C $(dir $(LIB)) fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
