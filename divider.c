/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:15:18 by awoods            #+#    #+#             */
/*   Updated: 2021/11/12 18:09:29 by awoods           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	divider_right(char *str, int i, int *code)
{
	if (str[i + 1] == '|' && (str[i + 2] == '|' || check_redirect(str[i + 2])))
		write_error_b(str, i, code);
	else if (str[i + 1] == ' ' && (str[i + 2] == '|' || \
	check_redirect(str[i + 2])))
		write_error_b(str, i, code);
}

void	divider_left(char *str, int i, int *code)
{
	if (str[i + 1] == '|')
		write_error_a(str, i, code);
	else if (str[i + 1] == ' ' && (str[i + 2] == '|' || \
	check_redirect(str[i + 2])))
		write_error_b(str, i, code);
}

void	divider_right_right(char *str, int i, int *code)
{
	if (check_redirect(str[i + 1]) || str[i + 1] == '|')
		write_error_a(str, i, code);
	else if (str[i + 1] == ' ' && (str[i + 2] == '|' || \
	check_redirect(str[i + 2])))
		write_error_b(str, i, code);
}

void	divider_left_left(char *str, int i, int *code)
{
	if (str[i + 1] == '|' || str[i + 1] == '>')
		write_error_a(str, i, code);
	else if (str[i + 1] == '<' && \
		(str[i + 2] == '|' || check_redirect(str[i + 2])))
		write_error_b(str, i, code);
	else if (str[i + 1] == ' ' && \
	(str[i + 2] == '|' || check_redirect(str[i + 2])))
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
