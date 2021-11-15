#ifndef MINISHELL_H
#define MINISHELL_H

# include "Libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>

# define MINI	"\033[32mMini$ \033[0m"
//# define MINI	"Mini$ "
# define BUFFER_SIZE 1

int g_status;

typedef struct s_lists
{
	char			*str;
	char			**ptr; /**argv*/
	struct s_lists	*next;
	int				end_code; /** termination code - код завершения. Изменяется при выведении ошибки */
	int				number_str;/**количество рагументов*/
	char			*operation; /** Redirects and Pipe*/
}				t_lists;

typedef struct s_flags
{
	int				start; /** координата делителя для листов и **ptr */
	int				code; /** код завершения программы в парсере*/
	int				quote;
	int				flag;
}				t_flags;

void	clear_list(t_lists **list, char *str);

/**cmd_utils*/
int	print_errno(void);

/**cmd_pwd*/
int	cmd_pwd(char **arg, char **env) ;

/**cmd_echo*/
int	cmd_echo(char **arg);

/**init_env*/
void	init_env(char ***env, char **envp);
int	cmd_env(char **arg, char **env);

/**cmd_export*/
int	cmd_export(char **arg, char **env);
int		equals(char *str);
void	sort_arg(char **env);
void	replace_var(char *arg, char **env);

/**cmd_unset*/
int	cmd_unset(char **arg, char **env);

/**cmd_cd*/
int	cmd_cd(char **arg, char **env);
int	new_work_directory(char **arg, char **env);
int	new_directory(char *home, char **env);
int	set_new_pwd(char **env);
int	set_new_oldpwd(char *pwd_old, char **env);

/**cd_utils*/
char *find_home_oldpwd(char **env, char *str);
int	check_to_oldpwd(char **env);
int	help_change_dir(char *oldpwd, char *home, char **env);
int	chdir_error(char *dir);

/**cmd_exit*/
int	cmd_exit(t_lists *new, char **env);

/**signal*/
void	signal_d(void);
void	signal_c(int sig);
void	signal_ign(void);
void	signal_dfl(void);

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
int	ft_lstsize(t_lists *lst);

/** creation_list.c */
t_lists	*creation_list(char *str, char **env);

/** write_array.c */
char	**write_array(char *str, t_lists **list, t_flags *flag);

/** pre_parsing.c */
int	pre_parsing(char **str);

/** delete_space.c */
char	*delete_space_top(char *str);
void	delete_space_middle(char **str);
char	*delete_space_bottom(char *str, int len);

/** check_space_divider.c */
char	*check_space_divider(char *str, int len);

/** divider.c */
void	divider_right(char *str, int i, int *code);
void	divider_left(char *str, int i, int *code);
void	divider_right_right(char *str, int i, int *code);
void	divider_left_left(char *str, int i, int *code);
void	divider_pipe(char *str, int i, int *code);

/** write_error.c */
void	write_error_a(char *str, int i, int *code);
void	write_error_b(char *str, int i, int *code);
void	write_error_c(char *str, int i, int *code);
void	write_error_d(char *str, int i, int *code);
int		write_error_e(char c);

/** check_symbol.c */
void	check_quotes(char *str, int *i);
int	check_pipe(char c);
int	check_redirect(char c);

/** parsing.c */
void	send_parsing(t_lists **list, char **env);




/** main_job.c */
void	main_job(t_lists **temp, char **env, int x);
void nav_cmd(char ***env, t_lists *new, int flag);


int	get_next_line(int fd, char **line);




#endif
