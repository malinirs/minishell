/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:41:52 by hparis            #+#    #+#             */
/*   Updated: 2021/11/16 23:44:15 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	**memory_allocation(int x, t_flags *flag, char **env)
{
	int	i;
	int	**fd;

	fd = malloc(sizeof(int *) * x);
	i = -1;
	while (++i < x)
		fd[i] = malloc(sizeof(int) * 2);
	flag->x = x;
	flag->env = env;
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

void	write_to_file(t_lists *list, int fd1)
{
	int	fd_file;

	while ((list)->operation[0] == '>')
	{
		if ((list)->operation[1] == '>')
			fd_file = open((list)->next->ptr[0], O_WRONLY | O_APPEND | O_CREAT, \
			0644);
		else
			fd_file = open((list)->next->ptr[0], O_WRONLY | O_CREAT | O_TRUNC, \
			0644);
		if ((list)->next->operation[0] != '>')
			dup2(fd_file, fd1);
		close(fd_file);
		list = (list)->next;
	}
}

void	take_from_file(t_lists *list, int fd0)
{
	int	fd_file;

	fd_file = open((list)->next->ptr[0], O_RDONLY);
	if (fd_file < 0)
	{
		write(2, (list)->next->ptr[0], ft_strlen((list)->next->ptr[0]));
		write(2, ": No such file or directory\n", 28);
		g_status = 1;
		exit(1);
	}
	dup2(fd0, fd_file);
	close(fd_file);
}

void	main_job(t_lists **list, char **env, int x, int i)
{
	t_flags	flag;
	int		**fd;
	t_lists	*temp;

	if (shlvl_up(list, env) == 1)
		return ;
	temp = *list;
	signal_pipe();
	if (x == 1)
	{
		command_lonly(temp, env);
		return ;
	}
	fd = memory_allocation(x, &flag, env);
	while (++i <= x - 1 && temp)
	{
		pipe(fd[i]);
		flag.pid = fork();
		if (flag.pid == 0)
			baby_process(temp, i, fd, &flag);
		else
			parent_process(&temp, i, fd, flag.pid);
	}
	signal_ign();
	memory_free(fd, x);
}
