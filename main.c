/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:33:16 by awoods            #+#    #+#             */
/*   Updated: 2021/10/25 18:36:44 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_lists *list)
{
	t_lists	*temp;

	list = NULL;
	while (list != NULL)
	{
		temp = list->next;
		free(list);
		list = temp;
	}
}

static t_lists	init_list(void)
{
	t_lists	list;

	list.end_code = 0;
	list.next = NULL;
	return (list);
}

void	creation_list(char *str, t_lists *list)
{
	list->ptr = ft_split(str, ' ');

	int i = -1;
	while(++i < 2 && list->ptr)
		printf("|%s|\n", list->ptr[i]);
}

void	parsing(char *str, char **env)
{
	int				i;
	i = -1;

	printf("str = %s\n", str);
	while (str[++i])
	{
		if (str[i] == '\'')
			str = pars_single_quotes(str, &i);
		if (str[i] == '$')
			str = pars_dollar(str, &i, env);
		if (str[i] == '\"')
			str = pars_double_quotes(str, &i, env);
	}
}

int main(int argc, char **argv, char **env)
{
	char	*str;
	t_lists	list;

	str = NULL;
	list.next = NULL;
	(void)argc;
	(void)argv;
	while (5)
	{
		if (str)
			free(str);
		if (list.end_code == 1)
			free_list(&list);
		str = readline(MINI);
		//		if (g_status == 130)
		//		{
		//			msh.old_status = 1;
		//			g_status = 0;
		//		}
		if (!str)
			str = ft_strdup("exit");
		add_history(str);
		parsing(str, env);
		list = init_list();
		creation_list(str, &list);
		/** Отдается в работу */
	}
}
