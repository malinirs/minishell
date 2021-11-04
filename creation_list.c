#include "minishell.h"

static int	check_sign(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

void	check_quotes(char *str, int *i)
{
	if (str[*i] == '\"')
		while (str[++(*i)] != '\"' && str[*i])
			;
		else if (str[*i] == '\'')
			while (str[++(*i)] != '\'' && str[*i])
				;
}

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

static t_lists	*creation_array(t_lists **list, t_flags	*flag)
{
	t_lists	*temp;

	int i;

	temp = *list;
	while (temp != NULL)
	{
		temp->ptr = write_array(temp->str, list, flag);

		i = 0;
		printf("ptr[%d] =", i);
		while (temp->ptr[i])
		{
			printf(" |%s|", temp->ptr[i]);
			i++;
		}
		printf("\n");

		temp = temp->next;
	}
	return (*list);
}

t_lists	*creation_list(char *str)
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
		else if (check_sign(str[i]) && str[i + 1] != '<' && str[i + 1] != '>')
			list = new_list_one(str, &flag, &list, i);
		else if (check_sign(str[i]) && (str[i + 1] == '<' || str[i + 1] == '>'))
			list = new_list_two(str, &flag, &list, &i);
	}
	list = new_list_one(str, &flag, &list, i);
	list = creation_array(&list, &flag);
	return (list);
}