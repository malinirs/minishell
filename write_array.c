#include "minishell.h"

char	*new_array(char *str, int i, t_flags *flag)
{
	char	*temp;

	temp = ft_substr(str, flag->start, i - flag->start);
	flag->start = i + 1;
	return (temp);
}

char	**counting_memory(char *temp, int *n, char **ptr, t_lists **list)
{
	int		i;
	char	**ptr2;

	(*n)++;
	ptr2 = (char **)malloc(sizeof(char *) * (*n + 1));
	i = -1;
	while (++i < (*n - 1))
		ptr2[i] = ptr[i];
	ptr2[i] = temp;
	ptr2[i + 1] = NULL;
//	i = n;
//	if (ptr)
//	{
//		while (--i >= 0)
//			free(ptr[i]);
//	}
//	(*list)->number_str = *n;
	return (ptr2);
}

char	**write_array(char *str, t_lists **list, t_flags *flag)
{
	int		i;
	char	**ptr;
	char	*temp;
	int		n;

	temp = NULL;
	ptr = NULL;
	i = 0;
	n = 1;
	flag->start = 0;
	(*list)->number_str = 0;
	while (i <= (int)ft_strlen(str))
	{
		if (str[i] == '\'' || str[i] == '\"')
			check_quotes(str, &i);
		else if (str[i] != ' ' || str[i] != '\0')
				i++;
		if (str[i] == ' ' || str[i] == '\0')
		{
			temp = new_array(str, i, flag);
			if (ptr == NULL)
			{
				ptr = malloc(sizeof(char *) * (n + 1));
				ptr[0] = temp;
				ptr[1] = NULL;
			}
			else
				ptr = counting_memory(temp, &n, ptr, list);
			i++;
		}
	}
	(*list)->number_str = n;

	printf("     ptr[0] = |%s|     \n", ptr[0]);
	printf("     ptr[1] = |%s|     \n", ptr[1]);
	printf("     ptr[2] = |%s|     \n", ptr[2]);

//	printf("ptr =");
//	i = -1;
//	while (ptr[++i])
//		printf(" %s", ptr[i]);
//	printf("\n");

//	n++;
//	temp = ft_substr(str, flag->start, i - flag->start);
//	ptr = counting_memory(temp, n, ptr, list);
//	(*list)->number_str++;
	return (ptr);
}