/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:59:07 by hparis            #+#    #+#             */
/*   Updated: 2021/11/16 16:36:40 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**проверка аргументов перед выполнением удаления*/
static int	chek_arg_error(char *arg)
{
	if (ft_strchr(arg, '=') || ft_strchr(arg, '.') || ft_strchr(arg, '/'))
	{
		write(2, "unset: \'", 8);
		write(2, arg, ft_strlen(arg));
		write(2, "\': not a valid identifier\n", 26);
		return (0);
	}
	return (1);
}

/**основной алгоритм для unset*/
int	cmd_unset(char **arg, char **env)
{
	int	i;
	int	j;
	int	len;

	j = 0;
	while (arg[++j])
	{
		i = -1;
		if (!chek_arg_error(arg[j]))
			continue ;
		len = ft_strlen(arg[j]);
		while (env && env[++i])
			if (!ft_strncmp(env[i], arg[j], len) && env[i][len] == '=')
				break ;
		free(env[i]);
		i -= 1;
		while (env[++i])
			env[i] = env[i + 1];
		env[i] = NULL;
	}
	return (0);
}
