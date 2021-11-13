#include "minishell.h"

void free_arg(char **arg)
{
	int i = -1;

	while(arg[++i])
		free(arg[i]);
	free(arg);
	arg=NULL;
}

int nav_cmd(char **arg, char ***env, t_flag data)
{
	int i;

	i = 0;
	if (arg[i])
	{
		if(!ft_strcmp("pwd", arg[i]))
			data.end_code = cmd_pwd(arg, *env);
		if(!ft_strcmp("echo -n", arg[i]) || !ft_strcmp("echo", arg[i]))
			data.end_code = cmd_echo(arg, *env);
		if (!ft_strcmp("env", arg[i]))
			data.end_code = cmd_env(arg, *env);
		if (!ft_strcmp("export", arg[i]))
			data.end_code = cmd_export(arg, *env);
		if (!ft_strcmp("unset", arg[i]))
			data.end_code = cmd_unset(arg, *env);
		if (!ft_strcmp("exit", arg[i]))
			data.end_code = cmd_exit(arg, *env);
		if (!ft_strcmp("cd", arg[i]))
			data.end_code = cmd_cd(arg, *env);
	}
	return(data.end_code);
}

int main(int argc, char **argv, char **envp)
{
	char   *str;
	char **env;
	char **arg;
	t_flag	data;

	(void)argc;
	(void)argv;
	str=NULL;
	init_env(&env, envp);
	data.end_code = 0;

	while (1)
	{
		if(str)
			free(str);
		str = readline(MSH_AVE);
		//    if (g_status == 130)
		//    {
		//       msh.old_status = 1;
		//       g_status = 0;
		//    }
		if (!str)
			str = ft_strdup("exit");
		add_history(str);
		arg=ft_split(str, ' ');
//    if (!parsing(&msh, str))
		printf("%d - ex\n", nav_cmd(arg, &env, data));

		free_arg(arg); /**очищает аргументы, чтобы не было ликов*/

		//       run_commands_via_pipes(&msh);
		//    cleaning(&msh, str);
	}
}
