/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:14:45 by awoods            #+#    #+#             */
/*   Updated: 2021/11/10 13:14:48 by awoods           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_space(int *i, int space, char *ptr)
{
	while (ptr[(*i)++] == ' ')
		space++;
	(*i)--;
	return (space);
}

static void	delete_space(char **ptr, int i, int space)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp1 = ft_substr(*ptr, 0, i + 1);
	temp2 = ft_substr(*ptr, i + space, (int)ft_strlen(*ptr) - (i + space));
	temp3 = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
	free(*ptr);
	*ptr = temp3;
}

char	*delete_space_top(char *str)
{
	int		i;
	char	*temp;
	int		space;

	i = 0;
	space = count_space(&i, 0, str);
	temp = ft_substr(str, i, (int)ft_strlen(str) - space);
	free(str);
	return (temp);
}

void	delete_space_middle(char **str)
{
	int		i;
	int		space;
	char	*ptr;

	ptr = *str;
	i = 0;
	while (ptr[i])
	{
		space = 0;
		if (ptr[i] == '\'' || ptr[i] == '\"')
			check_quotes(ptr, &i);
		else if (ptr[i] == ' ')
			space = count_space(&i, space, ptr);
		if (space > 1)
		{
			i = i - space;
			delete_space(&ptr, i, space);
		}
		i++;
	}
	*str = ptr;
}

char	*delete_space_bottom(char *str, int len)
{
	char	*temp;

	temp = ft_substr(str, 0, len - 1);
	free(str);
	return (temp);
}
