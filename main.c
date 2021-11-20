/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:10:43 by awoods            #+#    #+#             */
/*   Updated: 2021/11/16 23:47:05 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/termios.h>
#include "minishell.h"

void	nav_cmd(char ***env, t_lists *new, int flag)
{
	if (!ft_strcmp("pwd", new->ptr[0]))
		g_status = cmd_pwd(new->ptr, *env);
	else if (!ft_strcmp("echo", new->ptr[0]))
		g_status = cmd_echo(new->ptr, g_status);
	else if (!ft_strcmp("env", new->ptr[0]))
		g_status = cmd_env(new->ptr, *env);
	else if (!ft_strcmp("export", new->ptr[0]))
		g_status = cmd_export(new->ptr, *env);
	else if (!ft_strcmp("unset", new->ptr[0]))
		g_status = cmd_unset(new->ptr, *env);
	else if (!ft_strcmp("exit", new->ptr[0]))
		g_status = cmd_exit(new, *env);
	else if (!ft_strcmp("cd", new->ptr[0]))
		g_status = cmd_cd(new->ptr, *env);
	if (flag == 1)
		if (new->next->operation[0] == '|')
			return ;
}

void	clear_list(t_lists **list, char *str)
{
	t_lists	*temp;
	int		n;

	if (str)
		free(str);
	temp = *list;
	while (temp != NULL)
	{
		n = temp->number_str;
		while (n >= 0)
		{
			free(temp->ptr[n]);
			n--;
		}
		free(temp->ptr);
		free(temp->str);
		free(temp->operation);
		temp = temp->next;
	}
	free_list(list);
}

void	init(int argc, char **argv, char **str, t_lists **list)
{
	(void)argc;
	(void)argv;
	g_status = 0;
	*str = NULL;
	*list = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	**env;
	t_lists	*list;

	init(argc, argv, &str, &list);
	rl_outstream = stderr;
	init_env(&env, envp);
	signal_ign();
	while (5)
	{
		str = readline(MINI);
		if (!str)
			signal_d();
		add_history(str);
		if (pre_parsing(&str) == 0)
		{
			list = creation_list(str, env);
			main_job(&list, env, ft_lstsize(list), -1);
		}
		if (str || list)
			clear_list(&list, str);
	}
}
