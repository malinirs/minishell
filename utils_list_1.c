/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:13:38 by awoods            #+#    #+#             */
/*   Updated: 2021/11/16 16:36:41 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lists	*ft_lstnew(char *content)
{
	t_lists	*new;

	new = malloc(sizeof(t_lists));
	new->str = content;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_lists **lst, t_lists *new)
{
	t_lists	*new_lst;

	if (!lst && !new)
		return ;
	if (!*lst)
		*lst = new;
	new_lst = *lst;
	while (new_lst->next != NULL)
		new_lst = new_lst->next;
	new_lst->next = new;
	new->next = NULL;
}

void	free_list(t_lists **list)
{
	t_lists	*temp;

	while (*list != NULL)
	{
		temp = (*list)->next;
		free(*list);
		*list = temp;
	}
}

int	ft_lstsize(t_lists *lst)
{
	int		i;
	t_lists	*new_lst;

	if (!lst)
		return (0);
	i = 0;
	new_lst = lst;
	while (new_lst != NULL)
	{
		new_lst = new_lst->next;
		i++;
	}
	return (i);
}
