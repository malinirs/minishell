/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:14:26 by awoods            #+#    #+#             */
/*   Updated: 2021/11/16 23:15:42 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_divider_util(char *str, int *i, int *code, char *c)
{
	*c = str[*i];
	check_quotes(str, i);
	if (str[*i] == '\0')
		*code = write_error_e(*c);
}

int	check_divider(char *str, int i, int code, char c)
{
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			check_divider_util(str, &i, &code, &c);
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
		{
			g_status = code;
			return (1);
		}
	}
	return (0);
}

int	pre_parsing(char **str)
{
	if ((*str)[0] == ' ')
		*str = delete_space_top(*str);
	delete_space_middle(str);
	if ((*str)[(int)ft_strlen(*str) - 1] == ' ')
		*str = delete_space_bottom(*str, (int)ft_strlen(*str));
	if (check_divider(*str, -1, 0, ' ') == 1)
		return (1);
	*str = check_space_divider(*str, (int)ft_strlen(*str));
	return (0);
}
