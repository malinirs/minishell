/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:10:43 by awoods            #+#    #+#             */
/*   Updated: 2021/11/12 18:59:02 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	number_of_Redirects_and_Pipe(t_lists *list)
{
//	t_lists	*temp;
	int		count;

	count = 0;
//	temp = list;
	while (list != NULL)
	{
		if (list->operation[0])
			count++;
		list = list->next;
	}
	return (count);
}

int nav_cmd(char **arg, char ***env, t_lists new)
{
	int i;

	i = 0;
	if (arg[i])
	{
		if(!ft_strcmp("pwd", arg[i]))
			new.end_code = cmd_pwd(arg, *env);
		if(!ft_strcmp("echo -n", arg[i]) || !ft_strcmp("echo", arg[i]))
			new.end_code = cmd_echo(arg, *env);
		if (!ft_strcmp("env", arg[i]))
			new.end_code = cmd_env(arg, *env);
		if (!ft_strcmp("export", arg[i]))
			new.end_code = cmd_export(arg, *env);
		if (!ft_strcmp("unset", arg[i]))
			new.end_code = cmd_unset(arg, *env);
		if (!ft_strcmp("exit", arg[i]))
			new.end_code = cmd_exit(&new, *env);
		if (!ft_strcmp("cd", arg[i]))
			new.end_code = cmd_cd(arg, *env);
	}
	return(new.end_code);
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

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char **env;
	t_lists	*list;
	t_lists	*new;

	str = NULL;
	list = NULL;
	(void)argc;
	(void)argv;
	init_env(&env, envp);
	signal_ign();
	while (5)
	{
		str = readline(MINI);
		if (!str)
			signal_d();
		add_history(str);
		if (pre_parsing(&str) == 0)
			list = creation_list(str, env);

		new = list;
		while (new != NULL)
		{
			printf("list->ptr =");
			int i = -1;
			while (new->number_str > ++i)
				printf(" |%s|", new->ptr[i]);
			printf("    operation = %s\n", new->operation);
			new = new->next;
		}

		main_job(list, env, ft_lstsize(list));

		nav_cmd(list->ptr, &env, *list);

		if (str || list)
			clear_list(&list, str);

	}
}
