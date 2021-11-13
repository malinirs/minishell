/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:59:58 by hparis            #+#    #+#             */
/*   Updated: 2021/11/12 18:09:29 by awoods           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**сравнение строк используется в сортировке*/
static int	str_cmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (str1[i] == str2[i])
		return (0);
	return (str1[i] - str2[i]);
}

/**печать отсортированного массива c кавычками*/
static void	print_export(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (env[i][j] && env[i][j] != '=')
		{
			write(1, &env[i][j], 1);
			j++;
		}
		if (ft_strrchr(env[i], '='))
		{
			write(1, "=", 1);
			write(1, "\"", 1);
			while (env[i][++j])
				write(1, &env[i][j], 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}

/**сортировка env при отсутствии аргументов export*/
void	sort_arg(char **env)
{
	int		i;
	int		j;
	int		len_env;
	char	*tmp;

	i = 0;
	len_env = 0;
	while (env[len_env])
		len_env++;
	while (i < len_env)
	{
		j = 0;
		while (j < len_env - 1)
		{
			if (str_cmp(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	print_export(env);
}
