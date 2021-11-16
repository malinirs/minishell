/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:14:36 by hparis            #+#    #+#             */
/*   Updated: 2021/11/16 16:36:40 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	help_change_dir(char *oldpwd, char *home, char **env)
{
	if (chdir(home) == -1)
		return (chdir_error(home));
	if (oldpwd)
		if (set_new_oldpwd(oldpwd, env) != 0)
			return (print_errno());
	if (set_new_pwd(env) != 0)
		return (print_errno());
	return (0);
}

int	check_to_oldpwd(char **env)
{
	char	*oldpwd;

	oldpwd = find_home_oldpwd(env, "OLDPWD");
	if (oldpwd[0] == '\0')
		return (1);
	return (new_directory(oldpwd, env));
}

char	*find_home_oldpwd(char **env, char *str)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(str);
	while (env[++i])
	{
		if (!(ft_strncmp(env[i], str, len)))
		{
			if ((int)ft_strlen(env[i]) < (len + 1))
				break ;
			return (ft_strchr(env[i], '=') + 1);
		}
	}
	write(2, "minishell: cd : ", 16);
	write(2, str, len - 1);
	write(2, " not set\n", 9);
	return (NULL);
}

int	chdir_error(char *dir)
{
	write(2, "minishell: cd: ", 15);
	write(2, dir, ft_strlen(dir));
	write(2, ": ", 2);
	return (print_errno());
}
