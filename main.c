/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:33:16 by awoods            #+#    #+#             */
/*   Updated: 2021/11/05 18:58:52 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_list(t_lists **list)
{
	t_lists	*temp;
	int		n;

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

char	*parsing(char *str, char **env)
{
	int	i;
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
	return (str);
}

int main(int argc, char **argv, char **env)
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
		if (str) /** как правильно зафришить str? */
			free(str);
		if (list)
			clear_list(&list);
		str = readline(MINI);
		//		if (g_status == 130)
		//		{
		//			msh.old_status = 1;
		//			g_status = 0;
		//		}
		if (!str)
			str = ft_strdup("exit");
		add_history(str);

		list = creation_list(str);

//		str = parsing(str, env);
//		printf("str out = %s\n", str);
		//		list = creation_list_(str, 0, -1);


		new = list;
		while (new != NULL)
		{
			printf("list->str = %s ", new->str);
			printf("%s\n", new->operation);
			new = new->next;
		}

		/** Отдается в работу */
	}
}
