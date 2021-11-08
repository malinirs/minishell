#include "minishell.h"

int	check_pipe(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	check_redirect(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	check_divider(char *str)
{
	int	i;
	int	code;

	i = 0;
	code = 0;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>')//  && str[i + 2] != ' ')
			divider_right_right(str, ++i, &code);
		else if (str[i] == '<' && str[i + 1] == '<')//  && str[i + 2] != ' ')
			divider_left_left(str, ++i, &code);
		else if (str[i] == '>')//  && str[i + 1] != ' ')
			divider_right(str, i, &code);
		else if (str[i] == '<')// && str[i + 1] != ' ')
			divider_left(str, i, &code);
		else if (str[i] == '|')
			divider_pipe(str, i, &code);

		if (code != 0)
			return (code);
		i++;
	}
	return (code);


//		if ((str[i] == '>' && check_pipe(str[i + 1])) /** ??? */

		/** ls >    > 1, ls >>    > 1*/

}

/** cat >| 1 */

void	pre_parsing(char **str)
{
	t_flags	flag;

//	if (flag.code != 0)
//	{
//		free(*str);
//		exit(1);
//	}
	if ((*str)[0] == ' ')
		*str = delete_space_top(*str);
	delete_space_middle(str);
	if ((*str)[(int)ft_strlen(*str) - 1] == ' ')
		*str = delete_space_bottom(*str, (int)ft_strlen(*str));
	flag.code = check_divider(*str); /** если не 0, дальше не идем по программе*/

//	*str = check_space_divider(*str, (int)ft_strlen(*str));
}