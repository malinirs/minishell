/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:12:59 by awoods            #+#    #+#             */
/*   Updated: 2021/11/12 18:09:29 by awoods           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_subst(const char *s, int start, int len)
{
	int		i;
	int		j;
	char	*str;

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}

static char	*delete_quotes(char *str, int start, int i)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp2 = ft_substr(str, start + 1, i - start - 1);
	temp1 = ft_substr(str, 0, start);
	temp3 = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
	temp2 = ft_subst(str, i + 1, (int)ft_strlen(str));
	temp1 = ft_strjoin(temp3, temp2);
	free(temp3);
	free(temp2);
	return (temp1);
}

char	*pars_single_quotes(char *str, int *i)
{
	int		start;
	char	*temp;

	start = *i;
	while (str[++(*i)])
		if (str[*i] == '\'')
			break ;
	temp = delete_quotes(str, start, *i);
	free(str);
	*i = *i - 2;
	return (temp);
}

char	*pars_double_quotes(char *str, int *i, char **env)
{
	int		start;
	char	*temp1;
	int		finish;

	start = *i;
	while (str[++(*i)])
		if (str[*i] == '\"')
			break ;
	finish = *i - 2;
	temp1 = delete_quotes(str, start, *i);
	free(str);
	start--;
	while (++start <= finish)
		if (temp1[start] == '$')
			temp1 = pars_dollar(temp1, &start, env);
	*i = *i - 2;
	return (temp1);
}
