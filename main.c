/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:33:16 by awoods            #+#    #+#             */
/*   Updated: 2021/10/19 16:33:19 by awoods           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
