/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:19:21 by hparis            #+#    #+#             */
/*   Updated: 2021/11/12 18:09:29 by awoods           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**перезаписать переменную, если она уже есть в списке*/
void	repl_var_env(char *arg, char **env, int i)
{
	if (ft_strchr(arg, '='))
	{
		free(env[i]);
		env[i] = arg;
	}
}

/**считаем кол-во символов до =*/
int	equals(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

/**проверяет переменную в списке, если нет, добавляет новую*/
void	replace_var(char *arg, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], arg, equals(arg)))
		{
			repl_var_env(arg, env, i);
			return ;
		}
	}
	env[i] = arg ;
	env[++i] = NULL;
}

/**нужна ли проверка для аргументов без занка = */
static int	chek_exp(char *arg)
{
	if (arg[0] == '=' || ft_isdigit(arg[0]))
	{
		write(2, "export: \'", 9);
		write(2, arg, ft_strlen(arg));
		write(2, "\': not a valid identifier\n", 26);
		return (0);
	}
	return (1);
}

/**реализация export и добавление новой переменной*/
int	cmd_export(char **arg, char **env)
{
	int	j;

	j = 0;
	if (arg[1] == NULL)
		sort_arg(env);
	while (arg[++j] != NULL)
	{
		if (chek_exp(arg[j]))
			replace_var(arg[j], env);
	}
	return (0);
}
