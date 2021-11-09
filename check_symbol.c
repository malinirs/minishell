#include "minishell.h"

int	check_redirect(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	check_pipe(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

void	check_quotes(char *str, int *i)
{
	if (str[*i] == '\"')
		while (str[++(*i)] != '\"' && str[*i])
			;
		else if (str[*i] == '\'')
			while (str[++(*i)] != '\'' && str[*i])
				;
}
