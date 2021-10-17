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

char	*dollar(char *str, int *i, char **env)
{
	int		j;
	char	*temp;
	char	*temp2;
	char	*temp3;
	int		z;
	int	k = -1;

	z = 0;
	j = *i; /** координата начала */
	while (str[++(*i)])
	{
		if (!check_key(str[*i]))
			break ; /** координата конца */
	}
	if (*i == j + 1)
		return (str);
	temp = ft_substr(str, j + 1, *i - j - 1); /** скопировали */


	while (env[++k])
	{
		if (ft_strstr(env[k], temp))
		{
			while (env[k][z] != '=' && env[k][z])
				z++;
			temp2 = ft_substr(env[k], 0, z);
			if (ft_strcmp(temp, temp2) == 0) /** строки совпадают, если == 0 */
				break ;
		}
	}
	temp2 = ft_substr(env[k], z + 1, ft_strlen(env[k]) - z);
	printf("key = %s\n", temp);
	printf("temp2 = %s\n", temp2);
	//	free(str);
	return (temp);
}

void	parsing(char **argv, char **env)
{
	int		i;
	i = -1;


	char	*str = ft_strdup("co$USER mma'n\\nn'dd000\\'00cj\"mm\\\"\"an'dddd"
							 "'a");

	printf("str = %s\n", str);

	if (argv[0])
		i = -1;


	while (str[++i])
	{
		if (str[i] == '\'')
			str = pars_single_quotes(str, &i);
		if (str[i] == '$')
			str = dollar(str, &i, env);
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
