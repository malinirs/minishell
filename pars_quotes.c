#include "minishell.h"

static char	*delete_quotes(char *str, int start, int *i)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp1 = ft_substr(str, 0, start);
	temp2 = ft_substr(str, start + 1, *i - start - 1);
	temp3 = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
	temp2 = ft_substr(str, *i + 1, ft_strlen(str));
	temp1 = ft_strjoin(temp3, temp2);
	free(temp3);
	free(temp2);
	return (temp1);
}

char	*pars_single_quotes(char *str, int *i)
{
	int		start;
	char	*temp;

	start = *i; /** координата начала */
	while (str[++(*i)])
	{
		if (str[*i] == '\'')
			break ; /** координата конца */
	}
	temp = delete_quotes(str, start, i);

	printf("1_quotes1 = %s\n", temp);

	free(str);
	return (temp);
}

char	*pars_double_quotes(char *str, int *i, char **env)
{
	int		start;
	char	*temp1;

	start = *i; /** координата начала */
	while (str[++(*i)])
	{
		if (str[*i] == '\"')
			break ; /** координата конца */
	}
	temp1 = delete_quotes(str, start, i);
	free(str);
	start = -1;
	while (temp1[++start])
		if (temp1[start] == '$')
			temp1 = pars_dollar(temp1, &start, env);

	printf("1_quotes2 = %s\n", temp1);

	str = temp1;
	free(temp1);
	return (str);
}
