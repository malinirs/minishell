#include "minishell.h"

static void	adding_command(char	**path, char *str)
{
	int		i;
	char	*temp;

	i = -1;
	while (path[++i])
	{
		temp = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = ft_strjoin(temp, str);
		free(temp);
	}
}

static char	*search_and_split(char **env, char *str, int i)
{
	char	**path;
	char	*temp;

	while (env[++i])
		if (!ft_strncmp("PATH=", env[i], 5))
			break ;
	if (env[i] == NULL)
		return (NULL);
	path = ft_split(env[i], ':');
	temp = ft_substr(path[0], 5, ft_strlen(path[0]) - 5);
	free(path[0]);
	path[0] = temp;
	adding_command(path, str);
	i = -1;
	while (path[++i])
		if (!access(path[i], 1))
			break ;
	if (path[i] == NULL)
	{
		write (1, str, ft_strlen(str));
		write (1, ": command not found\n", 20);
		exit (127);
	}
	return (path[i]);
}

void	output(t_lists *list, char **env)
{
	char	*path;

	if (value(list))
		nav_cmd(&env, list, 1);
	else
	{
		path = search_and_split(env, list->ptr[0], -1);
		if (path == NULL)
		{
			write (2, list->ptr[0], ft_strlen(list->ptr[0]));
			write (2, ": Permission denied\n", 20);
			exit(126);
		}
		execve(path, list->ptr, env);
		write (2, list->ptr[0], ft_strlen(list->ptr[0]));
		write (2, ": command not found\n", 20);
		exit(127);
	}
}

void	status(int pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	g_status = WSTOPSIG(status);
}

static void	output_lonly(t_lists *list, char **env)
{
	char	*path;
	int		pid;

	if (value(list))
		nav_cmd(&env, list, 0);
	else
	{
	g_status = 100;
		pid = fork();
		if (pid == 0)
		{
			path = search_and_split(env, list->ptr[0], -1);
			if (path == NULL)
			{
				write (2, list->ptr[0], ft_strlen(list->ptr[0]));
				write (2, ": Permission denied\n", 20);
				exit(126);
			}
			execve(path, list->ptr, env);
			write(2, list->ptr[0], ft_strlen(list->ptr[0]));
			write(2, ": command not found\n", 20);
			exit(127);
		}
		else
			status(pid);
	}
}

void	command_lonly(t_lists *temp, char **env)
{
	if (temp->ptr[0][0] == '\0')
		write(1, "\n", 1);
	else
		output_lonly(temp, env);
}
