#include "minishell.h"

void	delete_character(char **ptr, int i, int space)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp1 = ft_substr(*ptr, 0, i);
	temp2 = ft_substr(*ptr, i + space, ft_strlen(*ptr) - i -space);
	temp3 = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
	free(*ptr);
	*ptr = temp3;
}

void	pre_parsing(char **str)
{
	char	*ptr;
	int		i;
	int		space;

	ptr = *str;
	i = 0;
	while (ptr[i])
	{
		space = 0;
		if (ptr[i] == '\'' || ptr[i] == '\"')
			check_quotes(ptr, &i);
		else if (ptr[i] == ' ')
			while (ptr[i++] == ' ')
				space++;
		if (space > 1)
		{
			delete_character(&ptr, i, space);
			i = i - space;
			/** доделать старт*/
		}
			/** удалить пробелы */
		i++;
	}
}