#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

# define MSH_AVE	"\033[32mMinishellOOOO$ \033[0m"

typedef struct s_flag
{
	int		end_code;

}				t_flag;


char	*ft_strstr(char *haystack, char *needle);
int		ft_strcmp(char *s1, char *s2);
char	*pars_dollar(char *str, int *i, char **env);
char	*pars_single_quotes(char *str, int *i);
char	*pars_double_quotes(char *str, int *i, char **env);


#endif
