/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:15:57 by awoods            #+#    #+#             */
/*   Updated: 2021/11/12 18:09:29 by awoods           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parsing(char *str, char **env)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			str = pars_single_quotes(str, &i);
		if (str[i] == '$')
			str = pars_dollar(str, &i, env);
		if (str[i] == '\"')
			str = pars_double_quotes(str, &i, env);
	}
	return (str);
}

void	send_parsing(t_lists **list, char **env)
{
	t_lists	*temp;
	int		i;

	temp = *list;
	while (temp != 0x0)
	{
		i = -1;
		while (temp->number_str > ++i)
			temp->ptr[i] = parsing(temp->ptr[i], env);
		temp = temp->next;
	}
}
