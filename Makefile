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



OBJS		=	$(patsubst %.c,%.o,$(SRCS))

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f

LIB			= ./Libft/libft.a
RDL			= -lreadline

all:		$(NAME)

%.o : %.c
			$(CC) $(CFLAGS) -c -g $< -o $@ $(INCLUDE)

$(NAME):	$(OBJS) $(OBJS_C)
			$(MAKE) -C $(dir $(LIB))
			$(CC) -o $(NAME) $(OBJS) $(LIB) $(RDL)

clean:
			$(RM) $(OBJS) $(OBJS:.o=.d)
			@make -C $(dir $(LIB)) clean

fclean:		clean
			@make -C $(dir $(LIB)) fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
