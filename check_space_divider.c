/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_space_divider.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:14:59 by awoods            #+#    #+#             */
/*   Updated: 2021/11/10 13:15:03 by awoods           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*delete_space_before_divider(char *str, int i, int len)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp1 = ft_substr(str, 0, i);
	temp2 = ft_substr(str, i + 1, len - 1);
	temp3 = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
	free(str);
	return (temp3);
}

static char	*delete_space_after_divider(char *str, int i, int len)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp1 = ft_substr(str, 0, i + 1);
	temp2 = ft_substr(str, i + 2, len - 1);
	temp3 = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
	free(str);
	return (temp3);
}

char	*check_space_divider(char *str, int len)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' && (str[i + 1] == '>' || str[i + 1] == '<' || \
		str[i + 1] == '|'))
			str = delete_space_before_divider(str, i, len);
		if ((str[i] == '>' || str[i] == '<' || str[i] == '|') && \
		str[i + 1] == ' ')
			str = delete_space_after_divider(str, i, len);
		i++;
	}
	return (str);
}
