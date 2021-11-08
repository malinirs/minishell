#include "minishell.h"

void	write_error_a(char *str, int i, int *code)
{
	*code = 258;
	write(2, "Mini: syntax error near unexpected token `", 42);
	write(2, &str[i + 1], 1);
	if (check_redirect(str[i + 2]) || check_pipe(str[i + 2]))
		write(2, &str[i + 2], 1);
	write(2, "'\n", 2);
}

void	write_error_b(char *str, int i, int *code)
{
	*code = 258;
	write(2, "Mini: syntax error near unexpected token `", 42);
	write(2, &str[i + 2], 1);
	if (check_redirect(str[i + 3]) || check_pipe(str[i + 3]))
		write(2, &str[i + 3], 1);
	write(2, "'\n", 2);
}

void	write_error_c(char *str, int i, int *code)
{
	*code = 258;
	write(2, "Mini: syntax error near unexpected token `", 42);
	write(2, &str[i + 3], 1);
	if (check_redirect(str[i + 4]) || check_pipe(str[i + 4]))
		write(2, &str[i + 4], 1);
	write(2, "'\n", 2);
}

void	write_error_d(char *str, int i, int *code)
{
	*code = 258;
	write(2, "Mini: syntax error near unexpected token `", 42);
	write(2, &str[i + 4], 1);
	if (check_redirect(str[i + 5]) || check_pipe(str[i + 5]))
		write(2, &str[i + 5], 1);
	write(2, "'\n", 2);
}

void	divider_right(char *str, int i, int *code)
{
	if (str[i + 1] == '|' && (str[i + 2] == '|' || check_redirect(str[i + 2])))
		write_error_b(str, i, code);
	else if (str[i + 1] == ' ' && (str[i + 2] == '|' || check_redirect(str[i + 2])))
		write_error_b(str, i, code);
}

void	divider_left(char *str, int i, int *code)
{
	if (str[i + 1] == '|')
		write_error_a(str, i, code);
	else if (str[i + 1] == ' ' && (str[i + 2] == '|' || check_redirect(str[i + 2])))
		write_error_b(str, i, code);
}

void	divider_right_right(char *str, int i, int *code)
{
	if (check_redirect(str[i + 1]) || str[i + 1] == '|')
		write_error_a(str, i, code);
	else if (str[i + 1] == ' ' && (str[i + 2] == '|' || check_redirect(str[i + 2])))
		write_error_b(str, i, code);
}

void	divider_left_left(char *str, int i, int *code)
{
	if (str[i + 1] == '|' || str[i + 1] == '>')
		write_error_a(str, i, code);
	else if (str[i + 1] == '<' && \
	(str[i + 2] == '|' || check_redirect(str[i	+ 2])))
		write_error_b(str, i, code);
	else if (str[i + 1] == ' ' && (str[i + 2] == '|' || check_redirect(str[i + 2])))
		write_error_b(str, i, code);
}

void	divider_pipe(char *str, int i, int *code)
{
	if (str[i + 1] == '<' && str[i + 2] == '|')
		write_error_b(str, i, code);
	else if (str[i + 1] == '>' && str[i + 2] == '<')
		write_error_b(str, i, code);
	else if (str[i + 1] == '>' && str[i + 2] == '|' && \
	(str[i + 3] == '|' || check_redirect(str[i + 3])))
		write_error_c(str, i, code);
	else if (str[i + 1] == '>' && str[i + 2] == '>' && \
	(str[i + 3] == '|' || check_redirect(str[i + 3])))
		write_error_c(str, i, code);
	else if (str[i + 1] == '<' && str[i + 2] == '<' && str[i + 3] == '<' && \
	(str[i + 4] == '|' || check_redirect(str[i + 4])))
		write_error_d(str, i, code);
	else if (str[i + 1] == ' ' && (str[i + 2] == '|'))
		write_error_a(str, i, code);
}
