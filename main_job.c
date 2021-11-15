#include "minishell.h"

void	adding_command(char	**path, char *str)
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

char	*search_and_split(char **env, char *str)
{
	char	**path;
	int		i;
	char	*temp;

	i = -1;
	while (env[++i])
		if (!ft_strncmp("PATH=", env[i], 5))
			break ;
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
		write (2, str, ft_strlen(str));
		write (2, ": command not found\n", 20);
		exit (127);
	}
	return (path[i]);
}

void	output(t_lists *list, char **env)
{
	char	*path;
	int		flag;

	flag = 1;

//	printf("list->ptr[0] = %s\n", list->ptr[0]);
	if (!ft_strcmp("echo", list->ptr[0]) || \
	!ft_strcmp("pwd", list->ptr[0]) || \
	!ft_strcmp("env", list->ptr[0]) || \
	!ft_strcmp("export", list->ptr[0]) || \
	!ft_strcmp("unset", list->ptr[0]) || \
	!ft_strcmp("exit", list->ptr[0]) || \
	!ft_strcmp("cd", list->ptr[0]))
		nav_cmd(&env, list, flag);
	else
	{
		path = search_and_split(env, list->ptr[0]);
//		printf("ASS\n");
		execve(path, list->ptr, env);
		write (2, list->ptr[0], ft_strlen(list->ptr[0]));
		write (2, ": command not found\n", 20);
		exit(127);
	}

}

void	output_lonly(t_lists *list, char **env)
{
	char	*path;
	int 	id;
	int		flag;

	flag = 0;

//	printf("list->ptr[0] = %s\n", list->ptr[0]);
	if (!ft_strcmp("echo", list->ptr[0]) || \
	!ft_strcmp("pwd", list->ptr[0]) || \
	!ft_strcmp("env", list->ptr[0]) || \
	!ft_strcmp("export", list->ptr[0]) || \
	!ft_strcmp("unset", list->ptr[0]) || \
	!ft_strcmp("exit", list->ptr[0]) || \
	!ft_strcmp("cd", list->ptr[0]))
		nav_cmd(&env, list, flag);
	else
	{
		id = fork();
		if (id == 0)
		{
			path = search_and_split(env, list->ptr[0]);
//			printf("ASS\n");
			execve(path, list->ptr, env);
			write(2, list->ptr[0], ft_strlen(list->ptr[0]));
			write(2, ": command not found\n", 20);
			exit(127);
		}
		else
			wait(NULL);
	}

}

int	**memory_allocation(int x)
{
	int	i;
	int	**fd;

	fd = malloc(sizeof(int *) * x);
	i = -1;
	while (++i < x)
		fd[i] = malloc(sizeof(int) * 2);
	return (fd);
}

void	write_in_file(t_lists *list, int fd0)
{
	int	fdFile;

	while ((list)->operation[0] == '>')
	{

		if ((list)->operation[1] == '>')
			fdFile = open((list)->next->ptr[0], O_WRONLY | O_APPEND | O_CREAT,
						  0644);
		else
			fdFile = open((list)->next->ptr[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if ((list)->next->operation[0] != '>')
			dup2(fdFile, fd0);
		close(fdFile);

		list = (list)->next;
	}
}


void	main_job(t_lists **list, char **env, int x)
{
	int		i;
	int		id;
	int		**fd;
	t_lists	*temp;


	temp = *list;
	if (x == 1)
	{
		output_lonly(temp, env);
		return;
	}
	fd = memory_allocation(x);
	i = -1;
	while (++i <= x - 1 && temp)
	{
		pipe(fd[i]);
		id = fork();
		if (id == 0) /** дочерний процесс */
		{
			if (i == x - 1) // last
			{
				close(fd[i][1]);
				dup2(fd[i - 1][0], 0);
			}
			else if (i == 0) // first
			{
				close(fd[i][0]);
				if (temp->operation[0] == '>')
				{
					close(fd[i][1]);
					write_in_file(temp, 1);
				}
				else
					dup2(fd[i][1], 1);
			}
			else // middle
			{
				dup2(fd[i - 1][0], 0);
				dup2(fd[i][1], 1);
				if (temp->operation[0] == '>')
				{
					write_in_file(temp, fd[i - 1][0]);
				}
				close(fd[i][0]);
			}
			output(temp, env);
		}
		else
		{
//			output(temp, env);


		wait(NULL);

//		char *line;
//		get_next_line(fd[i][0], &line);
//		printf("%s\n", line);
//		while (get_next_line(fd[i][0], &line))
//			printf("%s\n", line);
//		printf("%s\n", line);


			if (i > 0)
				close(fd[i - 1][0]);
			close(fd[i][1]);
			if (i > 0 && temp->operation[0] == '>')
				close(fd[i][0]);

			while (temp->operation[0] == '>')
			{
				temp = temp->next;
			}
			temp = temp->next;
		}
	}


//	if (i > 1)
//		close(fd[--i][0]);
	/** free fd */
}

//fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644); >
//fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT, 0644); >>

//int 	main(void)
//{
//	char *line;
//	int fd;
//
//	fd = open("text.txt", O_RDONLY);
//	while (get_next_line(fd, &line))
//		printf("%s\n", line);
//	printf("%s\n", line);
//	return (0);
//}