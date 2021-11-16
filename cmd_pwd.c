/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:19:48 by hparis            #+#    #+#             */
/*   Updated: 2021/11/16 16:36:40 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_pwd(char **arg, char **env)
{
	char	*buf;

	(void)arg;
	(void)env;
	buf = ft_calloc(1024, 1);
	if (getcwd(buf, 1024))
	{
		write(1, buf, ft_strlen(buf));
		write(1, "\n", 1);
		free(buf);
	}
	else
	{
		print_errno();
		free(buf);
	}
	return (0);
}
