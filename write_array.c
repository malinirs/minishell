/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:14:06 by awoods            #+#    #+#             */
/*   Updated: 2021/11/10 13:14:10 by awoods           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*new_array(char *str, int i, t_flags *flag)
{
	char	*temp;

	temp = ft_substr(str, flag->start, i - flag->start);
	flag->start = i + 1;
	return (temp);
}

static char	**counting_memory(char *temp, char **ptr, t_lists **list)
{
	int		i;
	char	**ptr2;

	(*list)->number_str++;
	ptr2 = (char **)malloc(sizeof(char *) * ((*list)->number_str + 1));
	i = -1;
	while (++i < ((*list)->number_str - 1))
		ptr2[i] = ptr[i];
	ptr2[i] = temp;
	ptr2[i + 1] = NULL;
	free(ptr);
	return (ptr2);
}

char	**write_array(char *str, t_lists **list, t_flags *flag)
{
	int		i;
	char	**ptr;
	char	*temp;

	ptr = NULL;
	i = -1;
	while (++i <= (int)ft_strlen(str))
	{
		if (str[i] == '\'' || str[i] == '\"')
			check_quotes(str, &i);
		else if (str[i] == ' ' || str[i] == '\0')
		{
			temp = new_array(str, i, flag);
			if (ptr == NULL)
			{
				ptr = malloc(sizeof(char *) * ((*list)->number_str + 1));
				ptr[0] = temp;
				ptr[1] = NULL;
			}
			else
				ptr = counting_memory(temp, ptr, list);
		}
	}
	return (ptr);
}
