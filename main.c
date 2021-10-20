/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:33:16 by awoods            #+#    #+#             */
/*   Updated: 2021/10/20 20:57:59 by                  ###   ########.fr       */
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
	temp = ft_substr(str, 0, j);
	temp2 = ft_substr(str, j + 1, *i - j - 1);
	temp3 = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
	temp2 = ft_substr(str, *i + 1, ft_strlen(str));
	temp = ft_strjoin(temp3, temp2);
	free(temp3);
	free(temp2);
	printf("1_quotes1 = %s\n", temp);
	return (temp);
}

char	*pars_double_quotes(char *str, int *i, char **env)
{
	int		j;
	char	*temp;
	char	*temp2;
	char	*temp3;
	int		flag_single_quotes;
	int		flag_dollar;

	flag_single_quotes = 0;
	flag_dollar = 0;
	j = *i; /** координата начала */
	while (str[++(*i)])
	{
		if (str[*i] == '\'')
			str = pars_single_quotes(str, i);
		if (str[*i] == '$')
			str = pars_dollar(str, i, env);
		if (str[*i] == '\"')
			break ; /** координата конца */
	}
//	if (flag_single_quotes == 1)
//		str = pars_single_quotes(str, *i);
//	if (flag_single_quotes == 0 && flag_dollar == 1)
//	{
//		temp = pars_dollar(str, i, env);
//		free(str);
//		str = temp;
//	}
	temp = ft_substr(str, 0, j);
	temp2 = ft_substr(str, j + 1, *i - j - 1);
	temp3 = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
	temp2 = ft_substr(str, *i + 1, ft_strlen(str));
	temp = ft_strjoin(temp3, temp2);
	free(temp3);
	free(temp2);
	printf("1_quotes1 = %s\n", temp);
	return (temp);
}

//t_pars_flags	assignment_flags(void)
//{
//	t_pars_flags	flags;
//
//
//	return (flags);
//}

void	parsing(char **argv, char **env)
{
	int				i;
//	t_pars_flags	flags;
	i = -1;

	char			*str = ft_strdup("$USER er'$USER'errer$USER");
	char			*str1;

//	str = argv[1];
	printf("str = %s\n", str);
//	flags = assignment_flags();
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
		if (str[i] == '\"')
		{
			str = pars_double_quotes(str, &i, env);
			free(str);
			str = str1;
		}
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
