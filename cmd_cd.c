/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:17:31 by hparis            #+#    #+#             */
/*   Updated: 2021/11/16 16:36:40 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_new_oldpwd(char *pwd_old, char **env)
{
	char	*pwd;

	pwd = ft_strjoin("OLDPWD=", pwd_old);
	replace_var(pwd, env);
	return (0);
}

int	set_new_pwd(char **env)
{
	char	*new_pwd;
	char	*tmp;
	char	*pwd;

	tmp = ft_calloc(1024, 1);
	pwd = getcwd(tmp, 1024);
	if (pwd == NULL)
		return (print_errno());
	new_pwd = ft_strjoin("PWD=", pwd);
	replace_var(new_pwd, env);
	free(tmp);
	return (0);
}

int	new_directory(char *home, char **env)
{
	char	*oldpwd;
	char	*tmp;

	tmp = ft_calloc(1024, 1);
	if (!tmp)
		print_errno();
	oldpwd = getcwd(tmp, 1024);
	free(tmp);
	return (help_change_dir(oldpwd, home, env));
}

int	new_work_directory(char **arg, char **env)
{
	if (ft_strcmp(arg[1], "-") == 0)
		return (check_to_oldpwd(env));
	if (ft_strcmp(arg[1], "~") == 0)
	{
		free(arg[1]);
		arg[1] = NULL;
		return (cmd_cd(arg, env));
	}
	else
		return (new_directory(arg[1], env));
}

int	cmd_cd(char **arg, char **env)
{
	int		i;
	char	*f_home;

	i = 0;
	while(arg[i])
		i++;
	if (i > 2)
	{
		write(2, "minishell: cd: to many arguments\n", 33);
		return (1);
	}
	if (i == 1)
	{
		f_home = find_home_oldpwd(env, "HOME=");
		if (f_home == NULL)
			return (1);
		new_directory(f_home, env);
	}
	if (i == 2)
		new_work_directory(arg, env);
	return (0);
}
