/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:00:31 by hparis            #+#    #+#             */
/*   Updated: 2021/11/16 16:36:40 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**инициализация переменных env*/
void	init_env(char ***env, char **envp)
{
	int	i;
	int	j;

	i = -1;
	while (envp[++i])
		;
	*env = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
	{
		(*env)[i] = malloc(ft_strlen(envp[i]) + 1);
		j = -1;
		while (envp[i][++j])
			(*env)[i][j] = envp[i][j];
		(*env)[i][j] = '\0';
	}
	(*env)[i] = NULL;
}

/**ошибка при лишних аргументах какое число возвращать при ошибке???*/
int	cmd_env(char **arg, char **env)
{
	int	i;

	i = -1;
	if (arg[1])
	{
		write(2, "env: ", 5);
		write(2, arg[1], ft_strlen(arg[1]));
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	while (env[++i])
	{
		if (ft_strchr(env[i], '='))
		{
			write(1, env[i], ft_strlen(env[i]));
			write(1, "\n", 1);
		}
	}
	return (0);
}
