#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include "Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

# define MINI	"\033[32mMini$ \033[0m"

typedef struct s_lists
{
	char			**ptr;
	struct s_lists	*next;
	int				end_code; /** termination code - код завершения. Изменяется при выведении ошибки */
}				t_lists;

char	*ft_strstr(char *haystack, char *needle);
int		ft_strcmp(char *s1, char *s2);
char	*pars_dollar(char *str, int *i, char **env);
char	*pars_single_quotes(char *str, int *i);
char	*pars_double_quotes(char *str, int *i, char **env);


#endif
