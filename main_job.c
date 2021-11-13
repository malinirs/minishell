#include "minishell.h"

void	final_output(t_lists *list, char **env, int x)
{


}

void	execution_program_builtins(char **ptr, char **env)
{

}

char	**search_and_split(char **env)
{
	char	*temp;
	char	**path;
	int		i;

	i = -1;
	while (env[++i])
		if (!ft_strcmp("PATH=", env[i]))
			temp = env[i];
	path = ft_split(temp, ':');

	write(1, "QWERTY", 7);

	return (path);
}

void	execution_program(char **ptr, char **env)
{
	char	**path;

	path = search_and_split(env);

	printf("path =");
	int	i = -1;
	while (path[++i])
		printf(" |%s|", path);
	printf("\n");

}

void	output(t_lists *list, char **env)
{
	if (!ft_strcmp("echo", list->ptr[0] || \
	!ft_strcmp("pwd", list->ptr[0]) || \
	!ft_strcmp("env", list->ptr[0]) || \
	!ft_strcmp("export", list->ptr[0]) || \
	!ft_strcmp("unset", list->ptr[0]) || \
	!ft_strcmp("exit", list->ptr[0]) || \
	!ft_strcmp("cd", list->ptr[0])))
		execution_program_builtins(list->ptr, env);
	else
		execution_program(list->ptr, env);
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

void	main_job(t_lists *list, char **env, int x)
{
	int	i;
	int	id;
	int	**fd;

	fd = memory_allocation(x);
	i = -1;
	while (++i <= x - 1)
	{
		pipe(fd[i]);
		id = fork();
		if (id == 0) /** дочерний процесс */
		{
			if (i == x - 1)
			{
				close(fd[i][1]);
				dup2(fd[i - 1][0], 0);
					/** прочесть из fd */
			}
			else if (!fd[i - 1][0])  // (i == 0)
			{
				close(fd[i][0]);
				dup2(fd[i][1], 1);
				/** прочесть с экрана
				записать в fd */
			}
			else
			{
				close(fd[i][0]);
				dup2(fd[i - 1][0], 0);
				dup2(fd[i][1], 1);
				/** прочитать из fd[0]
				записать в fd[1] */
			}
			output(list, env);
		}
		else
		{
//			wait();
//			текстовый файл = fd[i][1]); //как вывести? как узнать, сколько там
			// символов?

			/** вывести на экран, если не нужно записать в файл
			иначе запустить программу, кот записывает в файл
			закрыть fd */
			if (i > 0)
				close(fd[i - 1][0]);
			close(fd[i][1]);
			list = list->next;
		}
	}
	final_output(list, env, x);
	close(fd[--i][0]);
	/** free fd */
}

//fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644); >
//fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT, 0644); >>