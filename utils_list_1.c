#include "minishell.h"

t_lists	*ft_lstnew(char *content)
{
	t_lists	*new;


	new = malloc(sizeof(t_lists));
	new->end_code = 0;
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

//void	ft_lstadd_front(t_list	**lst, t_list	*new)
//{
//	if (!lst || !new)
//		return ;
//	new->next = *lst;
//	*lst = new;
//}
//
//void	ft_lstclear(t_list	**lst, void	(*del)(void*))
//{
//	t_list	*new_lst;
//
//	if (!*lst || !del)
//		return ;
//	while (*lst != NULL)
//	{
//		new_lst = (*lst)->next;
//		ft_lstdelone(*lst, del);
//		*lst = new_lst;
//	}
//}
//
//void	ft_lstdelone(t_list	*lst, void	(*del)(void*))
//{
//	if (!lst || !del)
//		return ;
//	del(lst->content);
//	free(lst);
//	lst = NULL;
//}
//
//void	ft_lstiter(t_list	*lst, void	(*f)(void *))
//{
//	t_list	*new_lst;
//
//	if (!lst)
//		return ;
//	new_lst = lst;
//	while (new_lst != NULL)
//	{
//		f(new_lst->content);
//		new_lst = new_lst->next;
//	}
//}
//
//t_list	*ft_lstlast(t_list	*lst)
//{
//	t_list	*new_lst;
//
//	if (!lst)
//		return (NULL);
//	new_lst = lst;
//	while (new_lst->next)
//		new_lst = new_lst->next;
//	return (new_lst);
//}
//
//t_list	*ft_lstmap(t_list	*lst, void	*(*f)(void *), void	(*del)(void *))
//{
//	t_list	*new;
//	t_list	*temp;
//
//	temp = NULL;
//	if (!lst || !f)
//		return (NULL);
//	while (lst != NULL)
//	{
//		new = ft_lstnew((*f)(lst->content));
//		if (!new)
//		{
//			ft_lstclear(&temp, del);
//			return (NULL);
//		}
//		else
//			ft_lstadd_back(&temp, new);
//		lst = lst->next;
//	}
//	return (temp);
//}
