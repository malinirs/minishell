/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:13:53 by awoods            #+#    #+#             */
/*   Updated: 2021/11/16 16:36:41 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lists	*new_list_one(char *str, t_flags *flag, t_lists **list, int i)
{
	char	*temp;
	t_lists	*new;

	temp = ft_substr(str, flag->start, i - flag->start);
	new = ft_lstnew(temp);
	new->operation = ft_substr(str, i, 1);
	ft_lstadd_back(list, new);
	flag->start = i + 1;
	return (*list);
}

static t_lists	*new_list_two(char *str, t_flags *flag, t_lists **list, int *i)
{
	char	*temp;
	t_lists	*new;

	temp = ft_substr(str, flag->start, *i - flag->start);
	new = ft_lstnew(temp);
	new->operation = ft_substr(str, *i, 2);
	ft_lstadd_back(list, new);
	flag->start = *i + 2;
	(*i)++;
	return (*list);
}

static void	creation_array(t_lists **list, t_flags	*flag)
{
	t_lists	*temp;

	temp = *list;
	while (temp != NULL)
	{
		flag->start = 0;
		temp->number_str = 1;
		temp->ptr = write_array(temp->str, &temp, flag);
		temp = temp->next;
	}
}

t_lists	*creation_list(char *str, char **env)
{
	int		i;
	t_lists	*list;
	t_flags	flag;

	list = NULL;
	i = -1;
	flag.start = 0;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			check_quotes(str, &i);
		else if (str[i] == '|')
			list = new_list_one(str, &flag, &list, i);
		else if (check_redirect(str[i]) && str[i + 1] != '<' && \
		str[i + 1] != '>')
			list = new_list_one(str, &flag, &list, i);
		else if (check_redirect(str[i]) && (str[i + 1] == '<' || \
		str[i + 1] == '>'))
			list = new_list_two(str, &flag, &list, &i);
	}
	list = new_list_one(str, &flag, &list, i);
	creation_array(&list, &flag);
	send_parsing(&list, env);
	return (list);
}
