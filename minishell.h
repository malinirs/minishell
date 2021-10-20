#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "Libft/libft.h"

typedef struct s_pars_flags
{
	bool	dollar;
}				t_pars_flags;

//int		ft_strlen(const char *str);
//char	*ft_strdup(const char *s1);
//char	*ft_substr(char *s, int start, int len);
//char	*ft_strjoin(char const *s1, char const *s2);
//int		ft_strlcpy(char *dst, const char *src, int dstsize);
//int		ft_isalnum(int c);
char	*ft_strstr(char *haystack, char *to_find);
int		ft_strcmp(char *s1, char *s2);
char	*pars_dollar(char *str, int *i, char **env);

#endif
