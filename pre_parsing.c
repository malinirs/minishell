/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:14:26 by awoods            #+#    #+#             */
/*   Updated: 2021/11/12 18:09:29 by awoods           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_divider(char *str, int i, int code, char c)
{
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			c = str[i];
			check_quotes(str, &i);
			if (str[i] == '\0')
				code = write_error_e(c);
		}
		else if (str[i] == '>' && str[i + 1] == '>')
			divider_right_right(str, ++i, &code);
		else if (str[i] == '<' && str[i + 1] == '<')
			divider_left_left(str, ++i, &code);
		else if (str[i] == '>')
			divider_right(str, i, &code);
		else if (str[i] == '<')
			divider_left(str, i, &code);
		else if (str[i] == '|')
			divider_pipe(str, i, &code);
		if (code != 0)
			return (code);
		i++;
	}
	return (code);
}

int	pre_parsing(char **str)
{
	if ((*str)[0] == ' ')
		*str = delete_space_top(*str);
	delete_space_middle(str);
	if ((*str)[(int)ft_strlen(*str) - 1] == ' ')
		*str = delete_space_bottom(*str, (int)ft_strlen(*str));
	g_status = check_divider(*str, 0, 0, ' ');
	if (g_status != 0)
		return (g_status);
	*str = check_space_divider(*str, (int)ft_strlen(*str));
	return (0);
}
