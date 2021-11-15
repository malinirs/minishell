/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:10:43 by awoods            #+#    #+#             */
/*   Updated: 2021/11/15 22:57:29 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/termios.h>
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

void nav_cmd(char ***env, t_lists *new, int flag)
{
		if(!ft_strcmp("pwd", new->ptr[0]))
			g_status = cmd_pwd(new->ptr, *env);
		else if(!ft_strcmp("echo", new->ptr[0]))
			g_status = cmd_echo(new->ptr);
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

void ctrl_ign(void)
{
	struct termios	ts;

	tcgetattr(STDIN_FILENO, &ts);
	ts.c_lflag = ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &ts);
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
	rl_outstream = stderr;
	init_env(&env, envp);
	ctrl_ign();
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


		if (str || list)
			clear_list(&list, str);

	}
}
