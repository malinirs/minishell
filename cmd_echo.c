/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:18:13 by hparis            #+#    #+#             */
/*   Updated: 2021/11/15 21:30:05 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_echo(char **arg)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_itoa(g_status);
	if (*arg && arg[1])
	{
		if (!ft_strcmp("-n", arg[1]))
			i++;

		while (arg[++i])
		{
			if (!ft_strcmp("$?", arg[1]))
				write(1, temp, ft_strlen(temp));
			else
				write(1, arg[i], ft_strlen(arg[i]));
			if (arg[i + 1])
				write(1, " ", 1);
		}
	}
	if (ft_strcmp("-n", arg[1]))
		write(1, "\n", 1);
	free(temp);
	return (0);
}
