/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:41:52 by hparis            #+#    #+#             */
/*   Updated: 2021/11/16 20:49:05 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	**memory_allocation(int x)
{
	int	i;
	int	**fd;

	fd = malloc(sizeof(int *) * x);
	i = -1;
	while (++i < x)
		fd[i] = malloc(sizeof(int) * 2);
	return (fd);
}

static void	memory_free(int	**fd, int x)
{
	int	i;

	i = -1;
	while (++i < x)
		free(fd[i]);
	free(fd);
	fd = NULL;
}

int	value(t_lists *list)
{
	if (!ft_strcmp("echo", list->ptr[0]) || \
	!ft_strcmp("pwd", list->ptr[0]) || \
	!ft_strcmp("env", list->ptr[0]) || \
	!ft_strcmp("export", list->ptr[0]) || \
	!ft_strcmp("unset", list->ptr[0]) || \
	!ft_strcmp("exit", list->ptr[0]) || \
	!ft_strcmp("cd", list->ptr[0]))
		return (1);
	return (0);
}

void	write_to_file(t_lists *list, int fd1)
{
	int	fdFile;

	while ((list)->operation[0] == '>')
	{

		if ((list)->operation[1] == '>')
			fdFile = open((list)->next->ptr[0], O_WRONLY | O_APPEND | O_CREAT, \
						  0644);
		else
			fdFile = open((list)->next->ptr[0], O_WRONLY | O_CREAT | O_TRUNC, \
						  0644);
		if ((list)->next->operation[0] != '>')
			dup2(fdFile, fd1);
		close(fdFile);

		list = (list)->next;
	}
}

void	take_from_file(t_lists *list, int fd0)
{
	int	fdFile;

	fdFile = open((list)->next->ptr[0], O_RDONLY);
	if (fdFile < 0)
	{
		write(2, (list)->next->ptr[0], ft_strlen((list)->next->ptr[0]));
		write(2, ": No such file or directory\n", 28);
		g_status = 1;
		exit(1);
	}
	dup2(fd0, fdFile);
	close(fdFile);
}

void	search_lvl(char **env, int i, t_flags *flag)
{
	while (env[++i])
		if (!ft_strncmp("SHLVL=", env[i], 6))
			break ;
	if (env[i] == NULL)
	{
		env[i] = malloc(sizeof(char) * 8);
		env[i] = ft_substr("SHLVL=1", 0, 6);
	}
	flag->temp = ft_substr(env[i], 6, ft_strlen(env[i]) - 6);
	flag->lvl = ft_atoi(flag->temp);
	free(flag->temp);
	flag->temp = ft_substr("SHLVL=1", 0, 6);
	flag->start = i;
}

int	shlvl_up(t_lists *list, char **env)
{
	char	*temp;
	t_flags	flag;

	search_lvl(env, -1, &flag);
	if (!ft_strcmp("mini", list->ptr[0]) || (!ft_strcmp("exit", list->ptr[0])
	&& flag.lvl > 1))
	{
		if (list->ptr[1] != NULL)
		{
			write(2, (list)->next->ptr[1], ft_strlen((list)->next->ptr[1]));
			write(2, ": No such file or directory\n", 28);
			g_status = 127;
		}
		else
		{
			if (!ft_strcmp("mini", list->ptr[0]))
				flag.lvl++;
			else if (flag.lvl > 1)
				flag.lvl--;
			temp = ft_itoa(flag.lvl);
			free(env[flag.start]);
			env[flag.start] = ft_strjoin(flag.temp, temp);
			free(flag.temp);
			free(temp);
		}
		return (1);
	}
	return (0);
}

void	main_job(t_lists **list, char **env, int x, int i)
{
	int		pid;
	int		**fd;
	t_lists	*temp;

	if (shlvl_up(*list, env) == 1)
		return ;
	temp = *list;
	signal_pipe();
	if (x == 1)
	{
		command_lonly(temp, env);
		return ;
	}
	fd = memory_allocation(x);
	while (++i <= x - 1 && temp)
	{
		pipe(fd[i]);
		pid = fork();
		signal_dfl();
		if (pid == 0)
			baby_process(x, temp, i, fd, env);
		else
			parent_process(&temp, i, fd, pid);
	}
	signal_ign();
	memory_free(fd, x);
}
