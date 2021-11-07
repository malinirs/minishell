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

void	write_error_a(char *str, int i)
{
	write(2, "Mini: syntax error near unexpected token `", 42);
	write(2, &str[i + 2], 1);
	if (check_redirect(str[i + 3]) || check_pipe(str[i + 3]))
		write(2, &str[i + 3], 1);
	write(2, "'\n", 2);
}

void	write_error_b(char *str, int i)
{
	write(2, "Mini: syntax error near unexpected token `", 42);
	write(2, &str[i + 2], 1);
	if (check_pipe(str[i + 3]))
		write(2, &str[i + 3], 1);
	write(2, "'\n", 2);
}

void	write_error_c(char *str, int i)
{
	write(2, "Mini: syntax error near unexpected token `", 42);
	write(2, &str[i + 2], 1);
	if (check_redirect(str[i + 4]) || check_pipe(str[i + 4]))
		write(2, &str[i + 4], 1);
	write(2, "'\n", 2);
}

void	write_error_d(char *str, int i)
{
	write(2, "Mini: syntax error near unexpected token `", 42);
	write(2, &str[i + 2], 1);
	if (check_pipe(str[i + 3]))
		write(2, &str[i + 3], 1);
	write(2, "'\n", 2);
}
void	write_error_e(char *str, int i)
{
	write(2, "Mini: syntax error near unexpected token `", 42);
	write(2, &str[i + 1], 1);
	if (check_redirect(str[i + 2]))
		write(2, &str[i + 2], 1);
	write(2, "'\n", 2);
}

int	check_divider(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		check_quotes(str, &i);
		if ((str[i] == '>' && str[i + 1] == '>' && check_redirect(str[i + 2])) || \
		((str[i] == '<' && str[i + 1] == '>') && check_redirect(str[i + 2])))
		{
			write_error_a(str, i);
			return (258); /** 258 */
		}
		if ((str[i] == '>' && str[i + 1] == '>' && check_pipe(str[i + 2])) || \
		(str[i] == '<' && str[i + 1] == '<' && check_pipe(str[i + 2])))
		{
			write_error_b(str, i);
			return (258);
		}
		if (str[i] == '<' && str[i + 1] == '<' && check_redirect(str[i + 2]))
		{
			write_error_c(str, i);
			return (258);
		}
//		if ((str[i] == '<' && str[i + 1] == '>') && check_redirect(str[i + 2]))
//		{
//			write_error_a(str, i);
//			return (258);
//		}
		if ((str[i] == '<' && str[i + 1] == '>') && check_pipe(str[i + 2]))
		{
			write_error_d(str, i);
			return (258);
		}
//		if ((str[i] == '>' && check_pipe(str[i + 1])) /** ??? */
		if (str[i] == '>' && str[i + 1] == '<')
		{
			write_error_e(str, i);
			return (258); /** 258 */
		}

		/** ls >    > 1, ls >>    > 1*/
		i++;
	}
	return (0);
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
	*str = check_space_divider(*str, (int)ft_strlen(*str));
}