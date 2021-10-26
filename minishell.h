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
	int				number_str;
}				t_lists;

typedef struct s_flags
{
	bool			implementation; /** еще есть команды в str для выполнения*/
}				t_flags;

int	number_str;

/** utils_1.c */
int		ft_isalnum(int c);
char	*ft_strstr(char *haystack, char *needle);
int		ft_strcmp(char *s1, char *s2);

/** pars_dollar.c */
char	*pars_dollar(char *str, int *i, char **env);

/** pars_quotes.c */
char	*pars_single_quotes(char *str, int *i);
char	*pars_double_quotes(char *str, int *i, char **env);

/** utils_list_1.c */
t_lists	*ft_lstnew(char **content);
void	ft_lstadd_back(t_lists **lst, t_lists *new);
void	free_list(t_lists **list);
int		ft_lstsize(t_lists *lst);

#endif
