/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:59:30 by hparis            #+#    #+#             */
/*   Updated: 2021/11/16 23:05:16 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**ошибка вывод*/
int	print_errno(void)
{
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 2);
	return (1);
}

void	search_lvl(char **env, int i, t_flags *flag)
{
	while (env[++i])
		if (!ft_strncmp("SHLVL=", env[i], 6))
			break ;
	if (env[i] == NULL)
	{
		env[i] = malloc(sizeof(char) * 8);
		env[i] = ft_substr("SHLVL=1", 0, 6);
	}
	flag->temp = ft_substr(env[i], 6, ft_strlen(env[i]) - 6);
	flag->lvl = ft_atoi(flag->temp);
	free(flag->temp);
	flag->temp = ft_substr("SHLVL=1", 0, 6);
	flag->start = i;
}

static void	writ_error(t_lists **list)
{
	write(2, (*list)->next->ptr[1], ft_strlen((*list)->next->ptr[1]));
	write(2, ": No such file or directory\n", 28);
	g_status = 127;
}

int	shlvl_up(t_lists **list, char **env)
{
	char	*temp;
	t_flags	flag;

	search_lvl(env, -1, &flag);
	if (!ft_strcmp("mini", (*list)->ptr[0]) || \
	(!ft_strcmp("exit", (*list)->ptr[0]) && flag.lvl > 1))
	{
		if ((*list)->ptr[1] != NULL)
			writ_error(list);
		else
		{
			if (!ft_strcmp("mini", (*list)->ptr[0]))
				flag.lvl++;
			else if (flag.lvl > 1)
				flag.lvl--;
			temp = ft_itoa(flag.lvl);
			free(env[flag.start]);
			env[flag.start] = ft_strjoin(flag.temp, temp);
			free(flag.temp);
			free(temp);
		}
		return (1);
	}
	return (0);
}

int	value(t_lists *list)
{
	if (!ft_strcmp("echo", list->ptr[0]) || \
	!ft_strcmp("pwd", list->ptr[0]) || \
	!ft_strcmp("env", list->ptr[0]) || \
	!ft_strcmp("export", list->ptr[0]) || \
	!ft_strcmp("unset", list->ptr[0]) || \
	!ft_strcmp("exit", list->ptr[0]) || \
	!ft_strcmp("cd", list->ptr[0]))
		return (1);
	return (0);
}
