/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:33:16 by awoods            #+#    #+#             */
/*   Updated: 2021/10/24 16:12:39 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(char *str, char **env)
{
	int				i;
	i = -1;

//	char	*str = ft_strdup("\"$USER $USER $USER\" $USER kmk");

	printf("str = %s\n", str);
	while (str[++i])
	{
		if (str[i] == '\'')
			str = pars_single_quotes(str, &i);
		if (str[i] == '$')
			str = pars_dollar(str, &i, env);
		if (str[i] == '\"')
			str = pars_double_quotes(str, &i, env);
	}
	printf("outcome = %s\n", str);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	char	*str;

	while (true)
	{
		str = readline(MSH_AVE);
//		if (g_status == 130)
//		{
//			msh.old_status = 1;
//			g_status = 0;
//		}
		if (!str)
			str = ft_strdup("exit");
		add_history(str);

		parsing(str, env);
//		if (!parsing(&msh, str))
//			run_commands_via_pipes(&msh);
//		cleaning(&msh, str);
	}



//	while (1);
	return (0);
}
