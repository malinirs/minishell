/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:10:43 by awoods            #+#    #+#             */
/*   Updated: 2021/11/10 13:44:09 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_list(t_lists **list, char *str)
{
	t_lists	*temp;
	int		n;

	if (str)
		free(str);
	temp = *list;
	while (temp != NULL)
	{
		n = temp->number_str;
		while (n >= 0)
		{
			free(temp->ptr[n]);
			n--;
		}
		free(temp->ptr);
		free(temp->str);
		free(temp->operation);
		temp = temp->next;
	}
	free_list(list);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_lists	*list;
	t_lists	*new;

	str = NULL;
	list = NULL;
	(void)argc;
	(void)argv;
	while (5)
	{
		str = readline(MINI);
		if (!str)
			str = ft_strdup("exit");
		add_history(str);
		if (pre_parsing(&str) == 0)
			list = creation_list(str, env);

		new = list;
		while (new != NULL)
		{
			printf("list->ptr =");
			int i = -1;
			while (new->number_str > ++i)
				printf(" |%s|", new->ptr[i]);
			printf("    operation = %s\n", new->operation);
			new = new->next;
		}

		if (str || list)
			clear_list(&list, str);
		/** Отдается в работу */
	}
}
