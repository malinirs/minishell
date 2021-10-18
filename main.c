#include "minishell.h"

char	*pars_single_quotes(char *str, int *i)
{
	int		j;
	char	*temp;
	char	*temp2;
	char	*temp3;


	j = *i; /** координата начала */
	while (str[++(*i)])
	{
		if (str[*i] == '\'')
			break ; /** координата конца */
	}
	temp = ft_substr(str, 0, j - 1); /** скопировали */
	temp2 = ft_substr(str, j + 1, *i - j);
	temp3 = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
	temp2 = ft_strdup(str + *i + 1);
	temp = ft_strjoin(temp3, temp2);
	free(temp3);
	free(temp2);
	printf("temp1 = %s\n", temp);
	//	free(str);
	return (temp);
}

int	check_key(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

char	*search_key(char **env, char *temp)
{
	char	*temp2;
	int		i;
	int		j;

	i = -1;
	j = 0;
	temp2 = NULL;
	while (env[++i])
	{
		if (ft_strstr(env[i], temp))
		{
			while (env[i][j] != '=' && env[i][j])
				j++;
			temp2 = ft_substr(env[i], 0, j);
			if (ft_strcmp(temp, temp2) == 0) /** строки совпадают, если == 0 */
				break ;
			else
				free(temp2);
		}
	}
	if (temp2 == NULL)
		return (NULL);
	temp2 = ft_substr(env[i], j + 1, ft_strlen(env[i]) - j);
	return (temp2);
}

char	*insertion_key(char *str, char *key, int first, int last)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp1 = ft_substr(str, 0, first);
	temp2 = ft_strjoin(temp1, key);
	free(temp1);
	temp1 = ft_substr(str, last, ft_strlen(str) - last);
	temp3 = ft_strjoin(temp2, temp1);
	free(temp1);
	free(temp2);

	printf("temp3 = %s\n", temp3);

	return (temp3);
}

char	*pars_dollar(char *str, int *i, char **env)
{
	int		j;
	char	*key;
	char	*meaning; /** значение */
	char	*temp;

	j = *i; /** координата начала */
	while (str[++(*i)])
	{
		if (!check_key(str[*i]))
			break ; /** координата конца */
	}
	if (*i == j + 1)
		return (str);
	key = ft_substr(str, j + 1, *i - j - 1); /** скопировали то, что после $ */
	meaning = search_key(env, key);
	free(key);
	if (meaning == NULL)
		return (str); /** Что делать в том случае, если не найден ключ???????? */
	temp = insertion_key(str, meaning, j, *i);
	free(str);
	free(meaning);
	return (temp);
}

void	parsing(char **argv, char **env)
{
	int		i;
	i = -1;

	char	*str = ft_strdup("co$USERmma'n\\nn'dd000\\'00cj\"mm\\\"\"an'dddda");
	char	*str1;

	printf("str = %s\n", str);

	if (argv[0])
		i = -1;

	while (str[++i])
	{
		if (str[i] == '\'')
		{
			str1 = pars_single_quotes(str, &i);
			free(str);
			str = str1;
		}
		if (str[i] == '$')
			str = pars_dollar(str, &i, env);
	}
}

int main(int argc, char **argv, char **env)
{

	if (argc > 1)
	{
		parsing(argv, env);
	}

//	while (1);
	return (0);
}
