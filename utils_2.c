#include "minishell.h"

int	ft_isalnum(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123) || (c > 47 && c < 58))
		return (1);
	else
		return (0);
}

char	*ft_strstr(char *haystack, char *needle)
/** находит первое вхождение строковой needle с нулевым символом в конце
 * в haystack строки с нулевым символом в конце */
{
	int i;
	int j;

	i = 0;
	if (needle[0] == '\0')
		return (haystack);
	while (haystack[i] != '\0')
	{
		j = 0;
		while (needle[j] != '\0')
		{
			if (haystack[i + j] != needle[j])
				break ;
			j++;
		}
		if (needle[j] == '\0')
			return (haystack + i);
		i++;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
/** сравнивает строки s1 и s2 с завершающим нулем */
{
	int	n;

	n = 0;
	while ((s1[n] != '\0') && (s2[n] != '\0') && (s1[n] == s2[n]))
		n++;
	if ((s1[n] == '\0') && (s2[n] == '\0'))
		return (0);
	else if ((s1[n] == '\0') && (s2[n] != '\0'))
		return (-1);
	else if ((s1[n] != '\0') && (s2[n] == '\0'))
		return (1);
	else
		return (s1[n] - s2[n]);
}
