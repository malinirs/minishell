/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:33:16 by awoods            #+#    #+#             */
/*   Updated: 2021/10/26 21:46:55 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_list(t_lists **list)
{
	t_lists	*temp;
	int	j;

	temp = *list;
	while (temp != NULL)
	{
		j = temp->number_str + 1;
		while (--j >= 0)
			free(temp->ptr[j]);
		free(temp->ptr);
		temp = temp->next;
	}
	free_list(list);
}

int	check_sign(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

static t_lists	*creation_list(char *str)
{
	t_lists	*list;
	t_lists	*new;
	char	**ptr;
	int		first;
	int		last;
	char	*temp1;

	list = NULL;
	new = NULL;
	last = -1;
	while (ft_strlen(str) > ++last)
	{
		first = last;
		while (str[last++])
			if (check_sign(str[last]))
				break ;
		temp1 = ft_substr(str, first, last - first);
		ptr = ft_split(temp1, ' ');
		printf("ptr = %s\n", ptr[0]);
		new = ft_lstnew(ptr);
		new->number_str = ft_check_nbr_str(temp1, ' ');
		ft_lstadd_back(&list, new);

		free(temp1);
	}

	new = list;
	while (new != NULL)
	{
		printf("list->ptr = %s\n", new->ptr[0]);
		new = new->next;
	}
	return (list);
}

char	*parsing(char *str, char **env)
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
	return (str);
}

int main(int argc, char **argv, char **env)
{
	char	*str;
	t_lists	*list;

	str = NULL;
	list = NULL;
	(void)argc;
	(void)argv;

	while (5)
	{
		if (str)
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
		str = parsing(str, env);
		list = creation_list(str);
//		free_list(&list);
//		free(str);
		/** Отдается в работу */
	}
}
