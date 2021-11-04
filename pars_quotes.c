#include "minishell.h"

char	*ft_subst(const char *s, int start, int len)
{
	int	i;
	int	j;
	char	*str;

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}

static char	*delete_quotes(char *str, int start, int i)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;

	printf("del  str = %s\n", str);
	printf("del  start = %d\n", start);
	printf("del  *i = %d\n", i);


	temp2 = ft_substr(str, start + 1, i - start - 1);
	temp1 = ft_substr(str, 0, start);

	printf("del11  str = %s\n", str);
	printf("del11  start = %d\n", start + 1);
	printf("del11  *i = %d\n", i - start - 1);


	printf("del temp1 = %s\n", temp1);
	printf("del temp2 = %s\n", temp2);


	temp3 = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
	int	b = (int)ft_strlen(str);

//	printf("ft_subst str = %s\n", str);
//	printf("ft_subst start = %d\n", *i + 1);
//	printf("ft_subst len = %d\n", b);

	temp2 = ft_subst(str, i + 1, b);

//	printf("del temp3 = %s\n", temp3);
//	printf("del temp2 = %s\n", temp2);

	temp1 = ft_strjoin(temp3, temp2);
	free(temp3);
	free(temp2);
	return (temp1);
}

char	*pars_single_quotes(char *str, int *i)
{
	int		start;
	char	*temp;

	start = *i; /** координата начала */
	while (str[++(*i)])
		if (str[*i] == '\'')
			break ; /** координата конца */


//	printf("single str = %s\n", str);
//	printf("single start = %d\n", start);
//	printf("single *i = %d\n", *i);


	temp = delete_quotes(str, start, *i);

	printf("1_quotes1 = %s\n", temp);


//	free(str);
	*i = *i - 2;
	str = temp;
	return (str);
}

char	*pars_double_quotes(char *str, int *i, char **env)
{
	int		start;
	char	*temp1;

	start = *i; /** координата начала */
	while (str[++(*i)])
		if (str[*i] == '\"')
			break ; /** координата конца */
	temp1 = delete_quotes(str, start, *i);
	free(str);
	start = -1;
	while (temp1[++start])
		if (temp1[start] == '$')
			temp1 = pars_dollar(temp1, &start, env);

	printf("1_quotes2 = %s\n", temp1);

	str = temp1;
	free(temp1);
	*i = *i - 2;
	return (str);
}
