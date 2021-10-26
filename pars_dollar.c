/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:32:10 by awoods            #+#    #+#             */
/*   Updated: 2021/10/24 16:45:57 by awoods           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*insertion_key(char *str, char *key, int first, int last)
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

	printf("dollar_vs = %s\n", temp3);

	return (temp3);
}

static char	*delete_key(char *str, int first, int last)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp1 = ft_substr(str, 0, first);
	temp2 = ft_substr(str, last, ft_strlen(str) - last);
	temp3 = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);

	printf("dollar_de = %s\n", temp3);

	return (temp3);
}

static char	*search_key(char **env, char *temp)
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
			free(temp2);
		}
	}
	if (temp2 == NULL)
		return (NULL);
	else
		free(temp2);
	temp2 = ft_substr(env[i], j + 1, ft_strlen(env[i]) - j);
	return (temp2);
}

static int	check_key(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

char	*pars_dollar(char *str, int *i, char **env)
{
	int		j;
	char	*key;
	char	*meaning; /** значение */
	char	*temp;

	j = *i; /** координата начала */
	while (str[++(*i)])
		if (!check_key(str[*i]))
			break ; /** координата конца */
	if (*i == j + 1)
		return (str);
	if (j - *i == 1)
		return ("$");
	key = ft_substr(str, j + 1, *i - j - 1);
	meaning = search_key(env, key);
	free(key);
	if (meaning)
	{
		temp = insertion_key(str, meaning, j, *i);
		free(meaning);
	}
	else
		temp = delete_key(str, j, *i);
	free(str);
	return (temp);
}
