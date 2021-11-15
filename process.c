#include "minishell.h"
#include <sys/wait.h>

void	parent_process(t_lists **temp, int i, int **fd)
{

	wait(NULL);
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

static void	baby_process_first(t_lists *temp, int i, int **fd)
{
	close(fd[i][0]);
	if (temp->operation[0] == '>')
	{
		close(fd[i][1]);
		write_to_file(temp, 1);
	}
	if (temp->operation[0] == '<')
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
	else if (temp->operation[0] == '<')
	{
		close(fd[i][1]);
		take_from_file(temp, 0);
	}
	else
		dup2(fd[i][1], 1);
	close(fd[i][0]);
}

void	baby_process(int x, t_lists *temp, int i, int **fd, char **env)
{
	if (i == x - 1) // last
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