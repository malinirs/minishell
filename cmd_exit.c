/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:18:55 by hparis            #+#    #+#             */
/*   Updated: 2021/11/12 18:56:17 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int no_number(char *arg)
{
	int i;

	i = 0;
	if (ft_strlen(arg) > 21)
		return (1);
	if (arg[0] == '+' || arg[0] == '-')
		i++;
	while (arg[i])
		if (ft_isdigit(arg[i++]) == 0)
			return (1);
	return (0);
}

//static int error_number(char *arg)
//{
//	write(2, "exit: ", 6);
//	write(2, arg, ft_strlen(arg));
//	write(2, ": numeric argument required\n", 28);
//	exit(255);
//	return (255);
//}

int	cmd_exit(t_lists *new, char **env)
{
	(void)env;

	if (new->number_str == 1)
		exit(new->end_code);
	if (new->number_str > 2)
	{
		write(2, "exit: too many arguments\n", 25);
		return (1);
	}
	if (no_number(new->ptr[1]))
		return (-1);//(error_number());
	if (new->number_str == 2)
		exit(ft_atoi(new->ptr[1]));
	return (0);
}
