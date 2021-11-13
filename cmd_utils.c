/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:59:30 by hparis            #+#    #+#             */
/*   Updated: 2021/11/12 18:09:29 by awoods           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	ft_strcmp(const char *s1, const char *s2)
//{
//	size_t	i;
//
//	i = 0;
//	while (s1[i] && s2[i])
//	{
//		if (s1[i] != s2[i])
//			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
//		i++;
//	}
//	if ((s1[i] == '\0' && s2[i]) || (s1[i] && s2[i] == '\0'))
//		return (1);
//	return (0);
//}

/**ошибка вывод*/
int	print_errno(void)
{
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 2);
	return (1);
}
