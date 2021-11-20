/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:18:07 by hparis            #+#    #+#             */
/*   Updated: 2021/11/16 23:28:25 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_d(void)
{
	ft_putstr_fd("\e[1A\e[6C" "exit\n", 1);
	exit (0);
}

void	signal_c(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_status = 130;
}
/**игнорирование, если мы в родительском процессе*/

void	signal_ign(void)
{
	signal(SIGINT, signal_c);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}
/**сделать дефолтными, если мы в дочке*/

void	signal_dfl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
}

/**игнорирование, если мы в дочернем процессе*/
void	signal_pipe(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}
