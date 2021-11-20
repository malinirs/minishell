/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 22:34:07 by awoods            #+#    #+#             */
/*   Updated: 2021/11/16 23:26:24 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_process(t_lists **temp, int i, int **fd, int pid)
{
	int	status;

	signal_dfl();
	waitpid(pid, &status, 0);
	g_status = WSTOPSIG(status);
	if (i > 0)
		close(fd[i - 1][0]);
	close(fd[i][1]);
	while ((*temp)->operation[0] == '>')
		*temp = (*temp)->next;
	if (i > 0 && ((*temp)->operation[0] == '>'))
		close(fd[i][0]);
	if ((*temp)->operation[0] == '<')
		*temp = (*temp)->next;
	*temp = (*temp)->next;
}

static void	heredoc(t_lists *temp, int fd)
{
	char	*str;

	while (4)
	{
		str = readline("> ");
		if (!ft_strcmp(temp->next->ptr[0], str))
			break ;
		write(temp->fd[1], str, ft_strlen(str));
		write(temp->fd[1], "\n", 1);
	}
	dup2(temp->fd[1], fd);
	dup2(fd, temp->fd[1]);
}

static void	baby_process_first(t_lists *temp, int i, int **fd)
{
	close(fd[i][0]);
	if (temp->operation[0] == '>')
	{
		close(fd[i][1]);
		write_to_file(temp, 1);
	}
	else if (temp->operation[1] == '<')
	{
		dup2(fd[i][1], 1);
		heredoc(temp, temp->fd[1]);
		close(temp->fd[0]);
	}
	else if (temp->operation[0] == '<')
	{
		close(fd[i][1]);
		take_from_file(temp, 0);
	}
	else
		dup2(fd[i][1], 1);
}

static void	baby_process_middle(t_lists *temp, int i, int **fd)
{
	dup2(fd[i - 1][0], 0);
	if (temp->operation[0] == '>')
	{
		close(fd[i][1]);
		write_to_file(temp, 1);
	}
	else if (temp->operation[1] == '<')
	{
		dup2(fd[i][1], 1);
		heredoc(temp, temp->fd[1]);
		close(temp->fd[0]);
	}
	else if (temp->operation[0] == '<')
	{
		close(fd[i][1]);
		take_from_file(temp, 0);
	}
	else
		dup2(fd[i][1], 1);
	close(fd[i][0]);
}

void	baby_process(t_lists *temp, int i, int **fd, t_flags *flag)
{
	char	**env;

	env = flag->env;
	signal_dfl();
	if (i == flag->x - 1)
	{
		close(fd[i][1]);
		if (temp->operation[0] == '<')
			take_from_file(temp, 0);
		dup2(fd[i - 1][0], 0);
	}
	else if (i == 0)
		baby_process_first(temp, i, fd);
	else
		baby_process_middle(temp, i, fd);
	output(temp, env);
}
