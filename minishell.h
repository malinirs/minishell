#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include "Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
//# include <errno.h>

# define MINI	"\033[32mMini$ \033[0m"

typedef struct s_lists
{
	char			*str;
	char			**ptr;
	struct s_lists	*next;
	int				end_code; /** termination code - код завершения. Изменяется при выведении ошибки */
	int				number_str;
	char			*operation; /** Redirects and Pipe*/
}				t_lists;
/** actions_file:
 * 0 - nothing
 * 1 - >
 * 2 - >>
 * 3 - <
 * 4 - <<
 * 5 - |   */



typedef struct s_flags
{
	bool			implementation; /** еще есть команды в str для выполнения*/
	int				start; /** координата делителя для листов и **ptr */
	int				code; /** код завершения программы */
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
t_lists	*ft_lstnew(char *content);
void	ft_lstadd_back(t_lists **lst, t_lists *new);
void	free_list(t_lists **list);

/** creation_list.c */
t_lists	*creation_list(char *str);
void	check_quotes(char *str, int *i);

/** write_array.c */
char	**write_array(char *str, t_lists **list, t_flags *flag);

/** pre_parsing.c */
void	pre_parsing(char **str);

/** delete_space.c */
char	*delete_space_top(char *str);
void	delete_space_middle(char **str);
char	*delete_space_bottom(char *str, int len);

/** check_space_divider.c */
char	*check_space_divider(char *str, int len);

#endif
