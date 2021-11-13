/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:18:13 by hparis            #+#    #+#             */
/*   Updated: 2021/11/11 11:18:21 by hparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**вывод аргумента на печать*/
static void	arg_echo(char *arg, char **env)
{
	char	*str;
	int		i;

	i = 0;
	if (arg && arg[0] == '$')
	{
		while (env && env[++i])
		{
			if (!ft_strncmp(env[i], (arg + 1), ft_strlen(arg) - 1))
			{
				str = ft_strrchr(env[i], '=') + 1;
				break ;
			}
		}
	}
	else
		str = arg;
	write(1, str, ft_strlen(str));
	return ;
}

/**команда echo*/
int	cmd_echo(char **arg, char **env)
{
	int	i;
	int	f;

	i = 0;
	f = 1;
	if (*arg && arg[1])
	{
		if (!ft_strcmp("-n", arg[1]))
		{
			i++;
			f = 0;
		}
		while (arg[++i])
		{
			arg_echo(arg[i], env);
			if (arg[i + 1])
				write(1, " ", 1);
		}
	}
	if (f)
		write(1, "\n", 1);
	return (0);
}
